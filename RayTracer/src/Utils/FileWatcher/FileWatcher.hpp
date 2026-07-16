/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** FileWatcher
*/

#pragma once
#include <sys/inotify.h>
#include <sys/select.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <errno.h>
#include <fcntl.h>
#include <chrono>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))
#define WATCH_TIMEOUT_MS 5000
#define DEBOUNCE_DELAY_MS 1000

namespace Raytracer
{
    extern volatile std::sig_atomic_t g_cancel_requested;
    extern void handleSignal(int sig);

    class FileWatcher {
        public:
            FileWatcher(std::string filename);
            ~FileWatcher();

            bool fileChanged();
            bool isInitialized() const;
    
        private:
            int _fd;
            int _watcher_fd;
            std::string _filename;
            std::chrono::steady_clock::time_point _last_change_time;
            bool _change_detected;
    };
    
} // namespace Raytracer
