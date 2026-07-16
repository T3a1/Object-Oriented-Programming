/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Menu
*/

#pragma once

    #include <iostream>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <filesystem>
    #include <string>

    #include "IGame.hpp"
    #include "Core.hpp"
    #include "ArcError.hpp"

namespace Arc
{
    /**
     * @class Menu
     * @brief Main menu interface for the Arcade application
     * 
     * The Menu class provides the user interface for selecting games and renderers.
     * It allows users to navigate through available games and rendering backends,
     * enter a username, and launch their selected game.
     * 
     * @details
     *   - **Game Selection**: Users can navigate through available games using LEFT/RIGHT arrows
     *   - **Renderer Selection**: Users can choose rendering backends using UP/DOWN arrows
     *   - **Username Input**: Support for alphanumeric username entry (max 10 characters)
     *   - **Game Launching**: Initiates the selected game with the chosen renderer
     *   - **High Score Display**: Shows the highest score for each game
     * 
     * @inherits IGame
     * @see IGame
     * @see Core
     */
    class Menu : public IGame
    {
        public:
            /**
             * @brief Constructs the Menu with game and renderer options
             * 
             * @param itemList Reference to the menu items map that will be populated
             * @param core Reference to the Core application controller
             * @param games Vector of available games (pair of name and path)
             * @param renderers Vector of available renderers (pair of name and path)
             */
            Menu(std::map<std::string, Item>& itemList, Core& core,
                 const std::vector<std::pair<std::string, std::string>>& games,
                 const std::vector<std::pair<std::string, std::string>>& renderers);
            
            /**
             * @brief Destructor
             */
            ~Menu() override;

            /**
             * @brief Updates menu state based on events
             * 
             * @param event The event to process
             * 
             * @note Currently unused as handleKey() is the primary event handler
             */
            void update([[maybe_unused]] Event event) override;
            
            /**
             * @brief Handles keyboard input for menu navigation and selection
             * 
             * Handles the following inputs:
             * - **LEFT/RIGHT arrows**: Navigate between games
             * - **UP/DOWN arrows**: Navigate between renderers
             * - **A-Z keys**: Enter username characters
             * - **BACKSPACE**: Delete last username character
             * - **ENTER**: Launch the selected game
             * - **ESC**: Quit the application
             * - **Mouse Click**: Activate buttons
             * 
             * @param event The keyboard event containing key information
             */
            void handleKey(Event event) override;
            
            /**
             * @brief Gets the game score (always 0 for menu)
             * @return A vector containing score of 0
             */
            std::vector<int> getScore() const override { return {0}; };
            
            /**
             * @brief Checks if the game is over (always false for menu)
             * @return false
             */
            bool isGameOver() const override { return false; };
            
            /**
             * @brief Retrieves the username entered by the player
             * @return The username string (max 10 characters)
             */
            std::string getUsername() const { return _username; };
            
            /**
             * @brief Retrieves the high score for a specific game
             * 
             * Reads the high score from the save directory for the specified game.
             * 
             * @param gamePath The game filename to read the score from
             * @return Formatted string with username and score, or "No Score" if not found
             * 
             * @details
             *   - Reads from `./save/{gamePath}.txt`
             *   - Expected format: `username:score`
             *   - Returns "No Score" if file doesn't exist or is malformed
             */
            std::string getHighScore(const std::string& gamePath) const;

        
            private:
                std::string _username = "";
                
                /**
                 * @brief Handles mouse click events on menu items
                 * 
                 * Checks if a click is within any clickable item's boundaries
                 * and triggers its associated action.
                 * 
                 * @param x X coordinate of the mouse click
                 * @param y Y coordinate of the mouse click
                 */
                void handleMouseClick(int x, int y);
                
                /**
                 * @brief Checks if a point is inside a rectangular item
                 * 
                 * @param x X coordinate of the point to check
                 * @param y Y coordinate of the point to check
                 * @param item The item to check collision against
                 * @return true if point is inside the item's bounding box, false otherwise
                 */
                bool isPointInRect(int x, int y, const Item& item) const;
                
                /**
                 * @brief Updates all game selection display items
                 * 
                 * Refreshes the game display text and high score information
                 * to reflect the current game selection.
                 */
                void updateGameItems();
                
                /**
                 * @brief Updates all renderer selection display items
                 * 
                 * Refreshes the renderer display text to reflect the current
                 * renderer selection.
                 */
                void updateRendererItems();
                
                std::map<std::string, Item>& _items;
                Core& _core;
                const std::vector<std::pair<std::string, std::string>>& _games;
                const std::vector<std::pair<std::string, std::string>>& _renderers;
    };
}
