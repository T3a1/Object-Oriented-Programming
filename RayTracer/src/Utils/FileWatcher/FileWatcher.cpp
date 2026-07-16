/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** FileWatcher
*/

#include "FileWatcher.hpp"

namespace Raytracer
{
    FileWatcher::FileWatcher(std::string filename)
        : _fd(-1), _watcher_fd(-1), _filename(filename), _change_detected(false)
    {
        _fd = inotify_init();
        if (_fd == -1) {
            std::cerr << "ERROR: inotify_init\n";
            return;
        }

        _watcher_fd = inotify_add_watch(_fd, _filename.c_str(), IN_MODIFY);
        if (_watcher_fd == -1) {
            std::cerr << "ERROR: Could not place watcher on " << _filename << "\n";
            close(_fd);
            _fd = -1;
            return;
        }
    }

    FileWatcher::~FileWatcher()
    {
        if (_watcher_fd != -1 && _fd != -1) {
            inotify_rm_watch(_fd, _watcher_fd);
        }
        if (_fd != -1) {
            close(_fd);
        }
    }

    bool FileWatcher::isInitialized() const
    {
        return _fd != -1 && _watcher_fd != -1;
    }

    bool FileWatcher::fileChanged()
    {
        if (!isInitialized())
            return false;

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(_fd, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        int select_result = select(_fd + 1, &readfds, nullptr, nullptr, &timeout);

        if (select_result == -1) {
            return false;
        }

        if (select_result > 0) {
            char buffer[EVENT_BUF_LEN];
            ssize_t bytes_read = read(_fd, buffer, EVENT_BUF_LEN);

            if (bytes_read == -1) {
                std::cerr << "ERROR: Failed to read inotify events\n";
                return false;
            }

            for (char *ptr = buffer; ptr < buffer + bytes_read; ) {
                struct inotify_event *event = (struct inotify_event *) ptr;

                if (event->mask & IN_MODIFY) {
                    _change_detected = true;
                    _last_change_time = std::chrono::steady_clock::now();
                }
                ptr += EVENT_SIZE + event->len;
            }
        }

        if (!_change_detected)
            return false;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - _last_change_time
        ).count();

        if (elapsed >= DEBOUNCE_DELAY_MS) {
            std::cerr << "Config file stable, reloading...\n";
            _change_detected = false;
            return true;
        }

        return false;
    }

} // namespace Raytracer
