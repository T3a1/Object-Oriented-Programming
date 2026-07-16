/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Snake
*/

#include "Snake.hpp"
#include <random>
#include <cstdlib>

namespace Arc
{
    Snake::Snake(std::map<std::string, Item>& itemList)
        : _items(itemList), _score(0), _game_over(false), _game_active(true), _moveDelayMs(120)
    {
        _lastCheck = std::chrono::steady_clock::now();
        reset();
    }

    Snake::~Snake()
    {
    }

    void Snake::reset()
    {
        _snake.clear();
        
        float midX = GRID_WIDTH / 2.0f;
        float midY = GRID_HEIGHT / 2.0f;
        
        _snake.push_back({midX, midY});
        _snake.push_back({midX - 1.0f, midY});
        _snake.push_back({midX - 2.0f, midY});
        
        _direction = {1.0f, 0.0f};
        _nextDirection = {1.0f, 0.0f};
        _score = 0;
        _game_over = false;
        _game_active = true;
        _lastCheck = std::chrono::steady_clock::now();
        
        spawnFood();
        updateItems();
    }

    void Snake::spawnFood()
    {
        bool valid = false;
        while (!valid) {
            float rx = static_cast<float>(rand() % static_cast<int>(GRID_WIDTH));
            float ry = static_cast<float>(rand() % static_cast<int>(GRID_HEIGHT));
            
            _food = {rx, ry};
            
            valid = true;
            for (const auto& segment : _snake) {
                if (segment.first == rx && segment.second == ry) {
                    valid = false;
                    break;
                }
            }
        }
    }

    bool Snake::checkCollision(const std::pair<float, float>& pos) const
    {
        if (pos.first < 0.0f || pos.first >= GRID_WIDTH ||
            pos.second < 0.0f || pos.second >= GRID_HEIGHT) {
            return true;
        }
        for (size_t i = 0; i < _snake.size() - 1; ++i) {
            if (_snake[i].first == pos.first && _snake[i].second == pos.second) {
                return true;
            }
        }
        
        return false;
    }

    void Snake::moveSnake()
    {
        _direction = _nextDirection;
        
        std::pair<float, float> newHead = {
            _snake.front().first + _direction.first,
            _snake.front().second + _direction.second
        };
        
        if (checkCollision(newHead)) {
            _game_active = false;
            return;
        }
        
        _snake.push_front(newHead);

        if (newHead.first == _food.first && newHead.second == _food.second) {
            _score += 10;
            spawnFood();
        } else {
            _snake.pop_back();
        }
    }

    void Snake::update(Event event)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastCheck).count();
        
        if (elapsed > _moveDelayMs) {
            _lastCheck = now;
            if (_game_active) {
                moveSnake();
            }
        }
        
        if (!_game_active) {
            _items["game_over"] = {
                {620, 80},
                {30, 30},
                0,
                {1.0f, 1.0f},
                false,
                1,
                "",
                "Game Over !\nMenu: Space\nRestart: R",
                std::function<void()>()
            };
        }
        updateItems();
    }

    void Snake::handleKey(Event event)
    {
        if (event.type == KeyPressed) {
            if (event.code == R) {
                reset();
                return;
            }
            if (event.code == Left && _direction.first != 1.0f) {
                _nextDirection = {-1.0f, 0.0f};
            }
            else if (event.code == Right && _direction.first != -1.0f) {
                _nextDirection = {1.0f, 0.0f};
            }
            else if (event.code == Up && _direction.second != 1.0f) {
                _nextDirection = {0.0f, -1.0f};
            }
            else if (event.code == Down && _direction.second != -1.0f) {
                _nextDirection = {0.0f, 1.0f};
            } else if (event.code == R) {
                _items.clear();
                reset();
            }
            if (!_game_active) {
                if (event.code == Space) {
                    _game_over = true;
                } 
            }
        }
    }

void Snake::updateItems()
{
    auto it = _items.begin();
    while (it != _items.end()) {
        if (it->first.substr(0, 6) == "snake_") {
            it = _items.erase(it);
        } else {
            ++it;
        }
    }

    _items["title"] = {
        {960.0f, 100.0f}, {0.02f, 0.02f}, 0, {1.0f, 1.0f}, false, 0, "", "SNAKE GAME", std::function<void()>()
    };

    _items["score"] = {
        {960.0f, 150.0f}, {0.02f, 0.02f}, 0, {1.0f, 1.0f}, false, 0, "",
        "Score: " + std::to_string(_score), std::function<void()>()
    };

    for (float x = -1.0f; x <= GRID_WIDTH; x += 1.0f) {
        _items["wall_top_" + std::to_string(static_cast<int>(x))] = {
            {OFFSET_X + x * CELL_SIZE, OFFSET_Y - CELL_SIZE}, {0.016f, 0.024f}, 0, {1.0f, 1.0f}, false, 0, "assets/wall.jpg", "#", std::function<void()>()
        };
        _items["wall_bot_" + std::to_string(static_cast<int>(x))] = {
            {OFFSET_X + x * CELL_SIZE, OFFSET_Y + GRID_HEIGHT * CELL_SIZE}, {0.016f, 0.024f}, 0, {1.0f, 1.0f}, false, 0, "assets/wall.jpg", "#", std::function<void()>()
        };
    }

    for (float y = 0.0f; y < GRID_HEIGHT; y += 1.0f) {
        _items["wall_left_" + std::to_string(static_cast<int>(y))] = {
            {OFFSET_X - CELL_SIZE, OFFSET_Y + y * CELL_SIZE}, {0.016f, 0.024f}, 0, {1.0f, 1.0f}, false, 0, "assets/wall.jpg", "#", std::function<void()>()
        };
        _items["wall_right_" + std::to_string(static_cast<int>(y))] = {
            {OFFSET_X + GRID_WIDTH * CELL_SIZE, OFFSET_Y + y * CELL_SIZE}, {0.016f, 0.024f}, 0, {1.0f, 1.0f}, false, 0, "assets/wall.jpg", "#", std::function<void()>()
        };
    }

    _items["food"] = {
            {OFFSET_X + _food.first * CELL_SIZE, OFFSET_Y + _food.second * CELL_SIZE},
            {0.034f, 0.033f}, 0, {1.0f, 1.0f}, false, 0, "assets/apple.jpg", "*", std::function<void()>()
        };

    for (size_t i = 0; i < _snake.size(); ++i) {
        std::string text = (i == 0) ? "O" : "o";
        float sizeX = (i == 0) ? 0.016f : 0.048f;
        float sizeY = (i == 0) ? 0.024f : 0.048f;
        _items["snake_" + std::to_string(i)] = {
            {OFFSET_X + _snake[i].first * CELL_SIZE, OFFSET_Y + _snake[i].second * CELL_SIZE},
            {sizeX, sizeY}, 0, {1.0f, 1.0f}, false, 0, (i == 0) ? "assets/wall.jpg" : "assets/play.jpg", text, std::function<void()>()
        };
    }
}

}

extern "C" {
        Arc::IGame* entryPoint([[maybe_unused]] std::map<std::string, Arc::Item>& itemList)
        {
            return new Arc::Snake(itemList);
        }

        int getLibraryType() {
            return static_cast<int>(Arc::LibraryType::Game); 
        }

        std::string getName() {
            return "Snake";
        }
}
