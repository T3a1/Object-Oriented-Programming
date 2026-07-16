/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#pragma once

    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>
    #include <vector>
    #include <memory>
    #include <filesystem>
    #include <type_traits>
    #include <dlfcn.h>
    #include <optional>

    #include "DLloader.hpp"
    #include "IRenderer.hpp"
    #include "IGame.hpp"
    #include "ArcError.hpp"
    #include "Utils.hpp"

namespace Arc
{
    /**
     * @struct LibraryMetadata
     * @brief Metadata information extracted from a dynamic library.
     */
    struct LibraryMetadata {
        std::string name;
        std::string path;
        LibraryType type;
    };

    /**
     * @class Core
     * @brief Main controller for the Arcade game launcher system.
     * 
     * Manages game launching, renderer switching, menu display, and
     * dynamic library loading and validation.
     */
    class Core
    {
        public:
            /**
             * @brief Initializes the Core with available libraries.
             * @param defaultRendererLib Path to the default renderer library
             * @param rendererLibs Vector of available renderer libraries
             * @param gameLibs Vector of available game libraries
             */
            Core(const std::string& defaultRendererLib, 
                 const std::vector<std::pair<std::string, std::string>>& rendererLibs,
                 const std::vector<std::pair<std::string, std::string>>& gameLibs);

            /**
             * @brief Destructor - cleans up loaded libraries.
             */
            ~Core();

            /**
             * @brief Starts the main event loop.
             */
            void run();

            /**
             * @brief Launches a game with a specific renderer.
             * @param gamePath Path to the game library
             * @param rendererPath Path to the renderer library
             */
            void launchGame(const std::string& gamePath, const std::string& rendererPath);

            /**
             * @brief Extracts metadata from a library file.
             * @param libPath Path to the library to examine
             * @return Optional metadata if valid, nullopt otherwise
             */
            static std::optional<LibraryMetadata> extractLibraryMetadata(const std::string& libPath);

            /**
             * @brief Validates that a library is a valid renderer.
             * @param rendererPath Path to the renderer library
             * @throws ErrorCritical if validation fails
             */
            static void validateDefaultRenderer(const std::string& rendererPath);

            bool _is_running;
            int _current_game_index = 0;
            int _current_renderer_index = 0;
            std::string _username;


        private:
            std::unique_ptr<Arc::DLloader<Arc::IRenderer>> _current_renderer_loader = nullptr;
            std::unique_ptr<Arc::DLloader<Arc::IGame>> _current_game_loader = nullptr;

            std::unique_ptr<Arc::IRenderer> _current_renderer = nullptr;
            std::unique_ptr<Arc::IGame> _current_game = nullptr;

            std::vector<std::pair<std::string, std::string>> _renderer_libs;
            std::vector<std::pair<std::string, std::string>> _game_libs;

            std::map<std::string, Item> _items;
            std::size_t _renderer_index;
            std::string _current_game_path;

            /**
             * @brief Loads the default renderer.
             * @param defaultRendererLib Path to the renderer library
             */
            void loadDefaultRenderer(const std::string& defaultRendererLib);

            /**
             * @brief Loads a renderer library.
             * @param rendererPath Path to the renderer library
             */
            void loadRenderer(const std::string& rendererPath);

            /**
             * @brief Loads the currently selected game.
             */
            void loadGame();

            std::size_t current_score = 0;

            /**
             * @brief Retrieves the high score for a game.
             * @param filename Filename containing the high score
             * @return Pair of (username, score)
             */
            std::pair<std::string, std::size_t> getHighScore(const std::string& filename) const;
    };
}
