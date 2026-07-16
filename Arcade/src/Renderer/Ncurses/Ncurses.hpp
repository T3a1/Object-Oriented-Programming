/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Ncurses
*/

#pragma once

    #include "IRenderer.hpp"
    #include <ncurses.h>

namespace Arc
{
    /**
     * @class Ncurses
     * @brief Terminal-based renderer using Ncurses library
     * 
     * The Ncurses class implements a text-based rendering backend that displays
     * the game on a terminal using the Ncurses library. This allows games to run
     * in any terminal environment without graphics dependencies.
     * 
     * @details
     *   - **Display Method**: Character-based terminal rendering
     *   - **Resolution**: Dynamic (default 120x40 characters)
     *   - **Performance**: Lightweight, suitable for remote connections
     *   - **Compatibility**: Works on any terminal with Ncurses support
     *   - **Color Support**: Basic terminal color pairs
     * 
     * @inherits IRenderer
     * @see IRenderer
     */
    class Ncurses : public IRenderer
    {
        public:
            /**
             * @brief Constructs a Ncurses renderer
             * 
             * Initializes the Ncurses library and sets up terminal mode.
             * Default dimensions are 120x40 characters with a 1:1 aspect ratio.
             */
            Ncurses();
            
            /**
             * @brief Destructor
             * 
             * Cleanly shuts down Ncurses and restores terminal to normal mode.
             */
            ~Ncurses() override;

            /**
             * @brief Renders all items to the terminal
             * 
             * Iterates through the item map and renders each item according to its
             * properties (position, size, text, texture). Displays the complete
             * rendered frame to the terminal.
             * 
             * @param itemList Reference to the map of items to render
             */
            void display(std::map<std::string, Item> &itemList) override;
            
            /**
             * @brief Retrieves and processes terminal input events
             * 
             * Reads keyboard input from the terminal and converts it to
             * Event objects. Handles special keys like arrows, Enter, Escape, etc.
             * 
             * @param event Reference to the Event object to populate
             * @return true if an event was captured, false otherwise
             */
            bool pollEvent(Event& event) override;
            
            /**
             * @brief Creates and initializes the terminal window
             * 
             * Sets up the terminal with the specified dimensions and title.
             * Configures the rendering area.
             * 
             * @param width Desired width in characters
             * @param height Desired height in characters
             * @param title Window title (displayed if supported)
             */
            void createWindow(int width, int height, const std::string& title) override;
            
            /**
             * @brief Clears the terminal display
             * 
             * Removes all content from the terminal, preparing it for
             * the next frame to be rendered.
             */
            void clear();
        
        private:
            float _ratio;
            int _maxX;
            int _maxY;
    };
}
