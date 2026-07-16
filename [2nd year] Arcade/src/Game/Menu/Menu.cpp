/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Menu
*/

#include "Menu.hpp"

Arc::Menu::Menu(std::map<std::string, Item>& itemList, Core& core,
                 const std::vector<std::pair<std::string, std::string>>& games,
                 const std::vector<std::pair<std::string, std::string>>& renderers)
    : _items(itemList), _core(core), _games(games), _renderers(renderers)
{
    itemList["menu_title"] = { 
        {480.0f, 200.0f}, {60.0f, 60.0f}, 0, {0, 0}, false, 0, "", "ARCADE MENU", std::function<void()>() 
    };
    itemList["menu_subtitle"] = { 
        {480.0f, 300.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", "Choisis ton jeu", std::function<void()>() 
    };
    
    updateGameItems();
    updateRendererItems();
    
    itemList["button_play"] = { 
        {350.0f, 520.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 2, "", "Play", 
        [this]() { 
            if (_core._current_game_index < static_cast<int>(_games.size()) && 
                _core._current_renderer_index < static_cast<int>(_renderers.size())) {
                try {
                    _core._username = getUsername();
                    _core.launchGame(_games[_core._current_game_index].second, 
                                    _renderers[_core._current_renderer_index].second);
                } catch (const AError& e) {
                    std::cerr << "[ERROR] Failed to launch game: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "[ERROR] Invalid game or renderer index!" << std::endl;
            }
        } 
    };
    
    itemList["button_quit"] = { 
        {610.0f, 520.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 2, "", "Quit", 
        [this](){ _core._is_running = false; } 
    };
    
    itemList["hint_text"] = { 
        {480.0f, 700.0f}, {20.0f, 20.0f}, 0, {0, 0}, false, 3, "", 
        "Use LEFT/RIGHT arrows to select | Press PLAY to start or ESC to quit", std::function<void()>() 
    };
}

Arc::Menu::~Menu()
{
}

void Arc::Menu::updateGameItems()
{
    if (_games.empty()) {
        _items["game_display"] = { 
            {480.0f, 380.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", "No games available", std::function<void()>() 
        };
        return;
    }

    int idx = _core._current_game_index % static_cast<int>(_games.size());
    _items["game_display"] = { 
        {480.0f, 380.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", 
        "< Game: " + _games[idx].first + " >", std::function<void()>()
    };
    _items["high_score"] = { 
        {480.0f, 420.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", 
        "High Score: " + getHighScore(_games[idx].first), std::function<void()>() 
    };
    _items["username"] = {
        {480.0f, 460.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", 
        "Username: " + _username, std::function<void()>() 
    };
}

void Arc::Menu::updateRendererItems()
{
    if (_renderers.empty()) {
        _items["renderer_display"] = { 
            {480.0f, 430.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", "No renderers available", std::function<void()>() 
        };
        return;
    }

    int idx = _core._current_renderer_index % static_cast<int>(_renderers.size());
    _items["renderer_display"] = { 
        {480.0f, 800.0f}, {40.0f, 40.0f}, 0, {0, 0}, false, 1, "", 
        "    ^    \nRenderer: " + _renderers[idx].first + "\n    v", std::function<void()>() 
    };
}

void Arc::Menu::update([[maybe_unused]] Event event)
{
}

void Arc::Menu::handleKey(Event event)
{
    if (event.type == KeyPressed) {
        if (event.code == MouseLeft) {
            handleMouseClick(event.mouse.x, event.mouse.y);
        }
        else if (event.code == Left) {

            if (!_games.empty()) {
                _core._current_game_index = (static_cast<int>(_core._current_game_index) - 1 + static_cast<int>(_games.size())) % static_cast<int>(_games.size());
                updateGameItems();
            }
        }
        else if (event.code == Right) {
            if (!_games.empty()) {
                _core._current_game_index = (static_cast<int>(_core._current_game_index) + 1) % static_cast<int>(_games.size());
                updateGameItems();
            }
        }
        else if (event.code == Up) {
            if (!_renderers.empty()) {
                _core._current_renderer_index = (static_cast<int>(_core._current_renderer_index) - 1 + static_cast<int>(_renderers.size())) % static_cast<int>(_renderers.size());
                updateRendererItems();
            }
        }
        else if (event.code == Down) {
            if (!_renderers.empty()) {
                _core._current_renderer_index = (static_cast<int>(_core._current_renderer_index) + 1) % static_cast<int>(_renderers.size());
                updateRendererItems();
            }
        }
        else if (event.code == Enter) {
            if (_items["button_play"].buttonAction) {
                _items["button_play"].buttonAction();
            }
        }
        else if (event.code == Escape) {
            if (_items["button_quit"].buttonAction) {
                _items["button_quit"].buttonAction();
            }
        }
        else if (event.code >= A && event.code <= Z) {
            if (_username.size() < 10) {
                _username += static_cast<char>('A' + (event.code - A));
                updateGameItems();
            }
        }
        else if (event.code == Backspace) {
            if (!_username.empty()) {
                _username.pop_back();
                updateGameItems();
            }
        }
    }
}

void Arc::Menu::handleMouseClick(int x, int y)
{
    for (auto it = _items.rbegin(); it != _items.rend(); ++it) {
        const Item& item = it->second;

        if (item.buttonAction && isPointInRect(x, y, item)) {
            item.buttonAction();
            return;
        }
    }
}

bool Arc::Menu::isPointInRect(int x, int y, const Item& item) const
{
    int rectX = static_cast<int>(item.position.first);
    int rectY = static_cast<int>(item.position.second);
    int rectW = static_cast<int>(item.size.first);
    int rectH = static_cast<int>(item.size.second);

    return (x >= rectX && x < rectX + rectW && y >= rectY && y < rectY + rectH);
}

std::string Arc::Menu::getHighScore(const std::string& filename) const {
    if (!std::filesystem::exists("./save")) {
        return "No Score";
    }

    std::ifstream file("./save/" + filename + ".txt");
    if (!file.is_open()) {
        return "No Score";
    }

    std::string line;
    if (!std::getline(file, line)) {
        return "No Score";
    }

    std::istringstream ss(line);
    std::string name, scoreStr;

    if (!std::getline(ss, name, ':') || !std::getline(ss, scoreStr)) {
        return "No Score";
    }

    return name + " " + scoreStr + " pts";
}
