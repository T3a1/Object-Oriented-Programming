/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Minesweeper
*/

#pragma once

    #include "IGame.hpp"
    #include "Utils.hpp"

    #include <cstdint>
    #include <random>
    #include <iomanip>
    #include <iostream>
    #include <queue>

    #define MINESWEEPER_WIDTH 10
    #define MINESWEEPER_HEIGHT 12
    #define MINESWEEPER_BOMBS 20

namespace Arc
{
    /**
     * @class Minesweeper
     * @brief Classic Minesweeper game implementation
     * 
     * The Minesweeper class implements the classic Minesweeper logic with a
     * 10x12 grid containing 20 randomly placed mines. Players must reveal cells
     * without hitting mines, using numerical clues to safely navigate the board.
     * 
     * @details
     *   - **Grid Size**: 10x12 cells (MINESWEEPER_WIDTH x MINESWEEPER_HEIGHT)
     *   - **Mines**: 20 randomly placed (MINESWEEPER_BOMBS)
     *   - **Game Mechanics**:
     *     - Left click: Reveal a cell
     *     - Right click: Flag/unflag a cell as potentially containing a mine
     *     - Numbers show adjacent mine count
     *     - Empty cells auto-reveal adjacent safe areas
     *   - **Win Condition**: Reveal all non-mine cells
     *   - **Lose Condition**: Reveal a mine
     * 
     * @inherits IGame
     * @see IGame
     */
    class Minesweeper : public IGame
    {
        public:
            /**
             * @enum GameState
             * @brief Represents the current state of the game
             */
            enum GameState
            {
                DEFEAT,
                VICTORY,
                INPROGRESS
            };

            /**
             * @brief Constructs a Minesweeper game instance
             * 
             * Initializes the grid and prepares all UI items.
             * Mines are spawned after the first click to ensure the first move is always safe.
             * 
             * @param itemList Reference to the item map for rendering UI elements
             */
            Minesweeper(std::map<std::string, Arc::Item>& itemList);
            
            /**
             * @brief Destructor
             */
            ~Minesweeper() override;

            /**
             * @brief Updates the game state each frame
             * 
             * Processes and detects win/lose conditions.
             * 
             * @param event The game event (unused)
             */
            void update([[maybe_unused]] Event event) override;
            
            /**
             * @brief Handles mouse input for cell interaction
             * 
             * Mouse events:
             * - **Left Click**: Reveal a cell
             * - **Right Click**: Flag/unflag a cell as a potential mine
             * 
             * @param event The mouse event containing click position
             */
            void handleKey(Event event) override;
            
            /**
             * @brief Gets the number of flagged cells (player's score)
             * @return Vector containing the flag count
             */
            std::vector<int> getScore() const override { return {_nb_flags}; };
            
            /**
             * @brief Checks if the game has ended
             * @return true if game is over (victory or defeat), false if still in progress
             */
            bool isGameOver() const override { return (_game_over) ; }

        private:
            /**
             * @struct Cell
             * @brief Represents a single cell in the Minesweeper grid
             */
            struct Cell
            {
                bool is_bomb = false; 
                bool is_revealed = false;
                bool is_flagged = false;
                std::uint8_t adjacent_bombs = 0;
            };

            std::vector<Cell> _grid;
            std::uint8_t _nb_flags;
            GameState _game_state; 
            bool _game_over;
            bool _has_started;

            std::map<std::string, Item>& _items;

            /**
             * @brief Checks if two grid cells are adjacent (including diagonals)
             * 
             * @param c1 Index of first cell
             * @param c2 Index of second cell
             * @return true if cells are adjacent, false otherwise
             */
            bool isAdjacent(std::size_t c1, std::size_t c2);
            
            /**
             * @brief Recursively reveals empty cells and their adjacent numbered cells
             * 
             * If a cell has 0 adjacent mines, automatically reveals all adjacent cells
             * and recursively continues for any empty adjacent cells.
             * 
             * @param index Index of the cell to start from
             */
            void revealEmptyArea(std::size_t index);
            
            /**
             * @brief Spawns mines randomly on the grid
             * 
             * Places MINESWEEPER_BOMBS mines on random cells, ensuring the first
             * clicked cell never contains a mine.
             * 
             * @param first_click Index of the player's first clicked cell
             */
            void spawnMines(std::size_t first_click);
            
            /**
             * @brief Calculates adjacent mine count for all cells
             * 
             * Called after mine placement to populate the adjacent_bombs
             * field for each cell.
             */
            void detectAdjacentMines();
            
            /**
             * @brief Handles right-click (flag toggle) on a cell
             * 
             * @param index Index of the cell to flag/unflag
             */
            void clickRight(std::size_t index);
            
            /**
             * @brief Handles left-click (reveal) on a cell
             * 
             * Reveals the cell and detects win/lose conditions.
             * Triggers recursive empty area reveal for cells with 0 adjacent mines.
             * 
             * @param index Index of the cell to reveal
             */
            void clickLeft(std::size_t index);
            
            /**
             * @brief Updates all visual UI grid items
             */
            void updateGrid();
            
            /**
             * @brief Handles user cell interaction (placeholder for future enhancements)
             */
            void handleCell();
            
            /**
             * @brief Converts mouse coordinates to grid cell index
             * 
             * @param x Mouse X coordinate
             * @param y Mouse Y coordinate
             * @return Cell index, or SIZE_MAX if click is outside the grid
             */
            std::size_t getCellIndexFromMouse(int x, int y);

            /**
             * @brief Displays debug grid information to console
             */
            void display() const;
    };
}
