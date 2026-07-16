/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IRenderer
*/

#pragma once

    #include <map>
    #include <string>

    #include "Event.hpp"
    #include "Utils.hpp"

namespace Arc
{
    /**
     * @interface IRenderer
     * @brief Abstract interface for graphics renderer implementations.
     * 
     * All renderer plugins must inherit from this interface and implement
     * these methods to be compatible with the Arcade launcher.
     */
    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            /**
             * @brief Renders all items on the display.
             * @param items Map of named items to render
             */
            virtual void display(std::map<std::string, Item>& items) = 0;

            /**
             * @brief Creates the display window.
             * @param width Window width in pixels
             * @param height Window height in pixels
             * @param title Window title
             */
            virtual void createWindow(int width, int height, const std::string& title) = 0;

            /**
             * @brief Polls for user input events.
             * @param event Output parameter populated with event data if available
             * @return true if an event was received, false otherwise
             */
            virtual bool pollEvent(Event& event) = 0;
    };
}
