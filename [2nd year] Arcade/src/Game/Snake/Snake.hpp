/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Snake Game Header
*/

#pragma once

#include "IGame.hpp"
#include <iostream>
#include <map>
#include <deque>
#include <chrono>

namespace Arc
{
    /**
     * @class Snake
     * @brief Classic Snake game implementation
     * 
     * The Snake class implements the classic Snake game mechanics where the player
     * controls a snake that grows by eating food while avoiding collisions with
     * walls and itself.
     * 
     * @details
     *   - **Grid-based gameplay**: 40x40 pixel grid cells
     *   - **Score System**: 1 point per food eaten
     *   - **Speed Control**: Movement delay increases with score
     *   - **Collision Detection**: Walls and self-collision
     *   - **Game Over State**: Detected via collision or manual termination
     * 
     * @inherits IGame
     * @see IGame
     */
    class Snake : public IGame
    {
        public:
            /**
             * @brief Constructs a Snake game instance
             * 
             * Initializes the snake at the center of the play area with one segment,
             * spawns initial food, and prepares all UI items.
             * 
             * @param itemList Reference to the item map for rendering UI elements
             */
            Snake(std::map<std::string, Arc::Item>& itemList);
            
            /**
             * @brief Destructor
             */
            ~Snake() override;

            /**
             * @brief Updates the game state each frame
             * 
             * Processes movement, collision detection, and food consumption.
             * Automatically speeds up as the score increases.
             * 
             * @param event The game event (unused)
             */
            void update(Event event) override;
            
            /**
             * @brief Handles keyboard input for snake control
             * 
             * Controls the direction of the snake movement:
             * - **UP arrow**: Move upward (if not moving down)
             * - **DOWN arrow**: Move downward (if not moving up)
             * - **LEFT arrow**: Move left (if not moving right)
             * - **RIGHT arrow**: Move right (if not moving left)
             * 
             * @param event The keyboard event
             * @note Prevents 180-degree turns (snake cannot reverse into itself)
             */
            void handleKey(Event event) override;
            
            /**
             * @brief Gets the current game score
             * @return Vector containing the current score (number of food eaten)
             */
            std::vector<int> getScore() const override { return {_score}; }
            bool isGameOver() const override { return _game_over; }

        private:
            /**
             * @brief Resets the game to initial state
             * 
             * Clears the snake, resets score and direction,
             * and spawns a new food.
             */
            void reset();
            
            /**
             * @brief Spawns food at a random location on the grid
             * 
             * Ensures the food doesn't spawn on the snake's current position.
             */
            void spawnFood();
            
            /**
             * @brief Moves the snake according to current direction
             * 
             * Adds a new head segment and removes the tail.
             * Handles food consumption by not removing the tail when food is eaten.
             */
            void moveSnake();
            
            /**
             * @brief Detects collision at a specific position
             * 
             * Checks for:
             * - Wall collision (outside game boundaries)
             * - Self collision (snake body overlap)
             * 
             * @param pos The position to check for collision
             * @return true if collision detected, false otherwise
             */
            bool checkCollision(const std::pair<float, float>& pos) const;
            
            /**
             * @brief Updates all visual UI items (snake, food, score display)
             */
            void updateItems();

            std::map<std::string, Item>& _items;
            
            std::deque<std::pair<float, float>> _snake;
            std::pair<float, float> _direction;
            std::pair<float, float> _nextDirection;
            std::pair<float, float> _food;
            
            int _score;
            bool _game_over;
            bool _game_active;
            
            std::chrono::steady_clock::time_point _lastCheck;
            int _moveDelayMs;
            
            const float GRID_WIDTH = 40.0f;
            const float GRID_HEIGHT = 30.0f;
            const float CELL_SIZE = 20.0f;
            const float OFFSET_X = 560.0f;
            const float OFFSET_Y = 240.0f;
    };
}
