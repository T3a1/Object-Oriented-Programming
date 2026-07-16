/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include "Menu.hpp"
#include <chrono>

Arc::Core::Core(const std::string& defaultRendererLib, 
                 const std::vector<std::pair<std::string, std::string>>& rendererLibs,
                 const std::vector<std::pair<std::string, std::string>>& gameLibs)
    : _is_running(true), _renderer_libs(rendererLibs), _game_libs(gameLibs), _renderer_index(0), _current_game_path("")
{
    loadDefaultRenderer(defaultRendererLib);

    _current_game = std::make_unique<Menu>(_items, *this, _game_libs, _renderer_libs);
}

Arc::Core::~Core()
{
    _current_game.reset();
    _current_renderer.reset();
    _current_game_loader.reset();
    _current_renderer_loader.reset();
}

std::optional<Arc::LibraryMetadata> Arc::Core::extractLibraryMetadata(const std::string& libPath)
{
    void* handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle)
        return std::nullopt;

    auto getType = reinterpret_cast<int (*)()>(dlsym(handle, "getLibraryType"));
    auto getName = reinterpret_cast<std::string (*)()>(dlsym(handle, "getName"));

    if (!getType || !getName) {
        dlclose(handle);
        return std::nullopt;
    }

    auto libName = getName();
    auto type = static_cast<LibraryType>(getType());
    
    dlclose(handle);

    return (LibraryMetadata) {libName, libPath, type};
}

void Arc::Core::validateDefaultRenderer(const std::string& rendererPath)
{
    void* handle = dlopen(rendererPath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw ErrorCritical("Cannot open library: " + rendererPath);
    }

    auto getType = reinterpret_cast<int (*)()>(dlsym(handle, "getLibraryType"));
    if (!getType) {
        dlclose(handle);
        throw ErrorCritical("Invalid library (missing getLibraryType): " + rendererPath);
    }

    auto type = static_cast<LibraryType>(getType());
    dlclose(handle);

    if (type != LibraryType::Renderer) {
        throw ErrorCritical("Default library must be a renderer: " + rendererPath);
    }
}

void Arc::Core::loadDefaultRenderer(const std::string& defaultRendererLib)
{
    loadRenderer(defaultRendererLib);
}

void Arc::Core::loadRenderer(const std::string& rendererPath)
{
    std::unique_ptr<Arc::DLloader<Arc::IRenderer>> loader = 
        std::make_unique<Arc::DLloader<Arc::IRenderer>>(rendererPath);
    
    Arc::IRenderer* instance = loader->getInstance(_items);
    if (!instance) {
        throw ErrorCritical("Cannot get renderer instance from: " + rendererPath);
    }

    _current_renderer.reset();
    _current_renderer_loader = std::move(loader);
    _current_renderer.reset(instance);
}

void Arc::Core::loadGame()
{
    std::unique_ptr<Arc::DLloader<Arc::IGame>> loader = 
        std::make_unique<Arc::DLloader<Arc::IGame>>(_current_game_path);
    
    Arc::IGame* instance = loader->getInstance(_items);
    if (!instance) {
        std::cerr << "[ERROR loadGame] Failed to create game instance from: " << _current_game_path << std::endl;
        throw ErrorCritical("Cannot get game instance from: " + _current_game_path);
    }

    _current_game.reset();
    _current_game_loader = std::move(loader);
    _current_game.reset(instance);
}

void Arc::Core::launchGame(const std::string& gamePath, const std::string& rendererPath)
{
    try {
        loadRenderer(rendererPath);
        _current_renderer->createWindow(1920, 1080, "Arcade");
        _items.clear();
        _current_game_path = gamePath;
        loadGame();
    } catch (const AError& e) {
        std::cerr << "[ERROR Core::launchGame] Exception caught: " << e.what() << std::endl;
        throw ErrorMajor(e.what());
    }
}

void Arc::Core::run()
{
    auto last_render_time = std::chrono::steady_clock::now();
    const std::chrono::milliseconds render_interval(16);

    if (!_current_game || !_current_renderer) {
        throw ErrorCritical("Problem loading libraries");
    }

    _current_renderer->createWindow(1920, 1080, "Arcade");

    try {
        while (_is_running) {
            Event event;

            while (_current_renderer->pollEvent(event)) {
                if (event.type == Quit) {
                    _is_running = false;
                    break;
                }
                if (!_current_game) {
                    std::cerr << "[ERROR] _current_game is null after event poll" << std::endl;
                    _is_running = false;
                    break;
                }

                if (event.type == KeyPressed && event.code == Tab) {
                    _renderer_index = (_renderer_index + 1) % 3;
                    loadRenderer(_renderer_libs[_renderer_index % 3].second);
                    _current_renderer->createWindow(1920, 1080, "Arcade");
                }

                _current_game->handleKey(event);
            }

            if (!_current_game || !_current_renderer) {
                break;
            }

            if (_current_game->isGameOver()) {
                std::string game_name("save/" + _game_libs[_current_game_index].first + ".txt");
                int score = _current_game->getScore()[0];

                std::pair<std::string, std::size_t> current_high_score= getHighScore(_game_libs[_current_game_index].first);
                if (score > current_high_score.second) {
                    std::ofstream out_save_file(game_name, std::ios::trunc);
                    out_save_file << _username << ":" << score;
                    out_save_file.close();
                }
                _items.clear();
                _current_game = std::make_unique<Menu>(_items, *this, _game_libs, _renderer_libs);
                continue;
            }

            auto now = std::chrono::steady_clock::now();
            auto elapsed = now - last_render_time;
            if (elapsed > render_interval) {
                _current_game->update(event);
                _current_renderer->display(_items);
                last_render_time = now;
            }
        }

    } catch (ErrorMajor& e) {
        std::cerr << "Major: " << e.what() << std::endl;
    }
}



/*

    HERE DONT PUSH

*/


std::pair<std::string, std::size_t> Arc::Core::getHighScore(const std::string& filename) const {
    if (!std::filesystem::exists("./save")) {
        return {"No Score", 0};
    }

    std::ifstream file("./save/" + filename + ".txt");
    if (!file.is_open()) {
        return {"No Score", 0};
    }

    std::string line;
    if (!std::getline(file, line)) {
        return {"No Score", 0};
    }

    std::istringstream ss(line);
    std::string name, scoreStr;

    if (!std::getline(ss, name, ':') || !std::getline(ss, scoreStr)) {
        return {"No Score", 0};
    }

    return {name, atoi(scoreStr.c_str())};
}
