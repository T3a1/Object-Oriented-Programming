/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IGame
*/

#pragma once

    #include <vector>
    #include <string>

    #include "Event.hpp"
    #include "Utils.hpp"

namespace Arc
{
    /**
     * @interface IGame
     * @brief Abstract interface for game implementations in the Arcade system.
     * 
     * All game plugins must inherit from this interface and implement these
     * pure virtual methods to be compatible with the Arcade launcher.
     */
    class IGame
    {
        public:
            virtual ~IGame() = default;

            /**
             * @brief Updates the game state based on the received event.
             * @param event The event to process (key press, mouse, etc.)
             */
            virtual void update([[maybe_unused]] Event event) = 0;

            /**
             * @brief Handles keyboard inputs for the game.
             * @param event The keyboard event to handle
             */
            virtual void handleKey(Event event) = 0;

            /**
             * @brief Retrieves the current game score.
             * @return Vector of integers representing the score(s)
             */
            virtual std::vector<int> getScore() const = 0;

            /**
             * @brief Checks if the game is over.
             * @return true if the game is over, false otherwise
             */
            virtual bool isGameOver() const = 0;
    };
}
