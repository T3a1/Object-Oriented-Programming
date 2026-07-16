/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sfml
*/

#pragma once

    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <iostream>
    #include <map>
    #include <vector>
    #include <algorithm>

    #include "IRenderer.hpp"
    #include "ArcError.hpp"

    #define FONT_SIZE 15
    #define TEXT_COLOR_R 255
    #define TEXT_COLOR_G 255
    #define TEXT_COLOR_B 255
    #define RATIO 20
    #define FONT_PATH "assets/AdwaitaMono-Regular.ttf"

namespace Arc
{
    /**
     * @class Sfml
     * @brief Graphics renderer using SFML (Simple and Fast Multimedia Library)
     * 
     * The Sfml class provides a renderer implementation using SFML, offering
     * a modern object-oriented graphics API with excellent performance and 
     * cross-platform compatibility.
     * 
     * @details
     *   - **Rendering**: Fast hardware-accelerated graphics via SFML
     *   - **Font Support**: TrueType fonts with dynamic size caching
     *   - **Texture Support**: Image loading and caching for efficiency
     *   - **Cross-platform**: Windows, Linux, macOS support
     *   - **Performance**: Optimized with size-based font and path-based texture caching
     *   - **Graphics Features**: Sprites, shapes, and text rendering
     * 
     * @inherits IRenderer
     * @see IRenderer
     */
    class Sfml : public IRenderer
    {
        public:
            /**
             * @brief Constructs an SFML renderer
             * 
             * Initializes the SFML library structures but defers window
             * creation to createWindow().
             */
            Sfml();
            
            /**
             * @brief Destructor
             * 
             * Cleans up all SFML resources including the render window,
             * cached fonts, and cached textures.
             */
            ~Sfml() override;

            /**
             * @brief Renders all items to the SFML window
             * 
             * Clears the window, processes all items in draw order,
             * and displays the complete frame.
             * 
             * @param itemList Reference to the map of items to render
             * @see renderItems(), renderItem()
             */
            void display(std::map<std::string, Item> &itemList) override;
            
            /**
             * @brief Retrieves and processes input events from SFML
             * 
             * Polls for SFML window and input events, converting them
             * to the internal Event format. Handles keyboard, mouse, and window events.
             * 
             * @param event Reference to the Event object to populate
             * @return true if an event was captured, false if no events pending
             */
            bool pollEvent(Event& event) override;
            
            /**
             * @brief Creates and initializes the SFML render window
             * 
             * Creates an SFML RenderWindow with specified dimensions and title,
             * ready for rendering.
             * 
             * @param width Window width in pixels
             * @param height Window height in pixels
             * @param title Window title displayed in the title bar
             * 
             * @throws AError if window creation fails
             */
            void createWindow(int width, int height, const std::string& title) override;
            
            /**
             * @brief Clears the window for the next frame
             * 
             * Fills the entire window with black color and prepares it
             * for new rendering content.
             */
            void clear();

        private:
            sf::RenderWindow* _window;
            sf::Font* _font;
            std::map<int, sf::Font*> _font_cache;
            std::map<std::string, sf::Texture*> _texture_cache;

            /**
             * @brief Retrieves or loads a font for the specified size
             * 
             * Maintains a cache of fonts by size to avoid redundant file I/O
             * and initialization overhead.
             * 
             * @param size Font size in points
             * @return Pointer to sf::Font, or nullptr if loading fails
             */
            sf::Font* getFontForSize(int size);
            
            /**
             * @brief Retrieves or loads a texture from the specified file path
             * 
             * Caches textures by file path for performance optimization.
             * Textures are loaded once and reused for all subsequent requests.
             * 
             * @param path File path to the image asset
             * @return Pointer to sf::Texture, or nullptr if loading fails
             */
            sf::Texture* getTextureForPath(const std::string& path);
            
            /**
             * @brief Renders all items according to their draw order
             * 
             * Internal method that iterates through the item collection
             * and renders each one in priority order.
             * 
             * @param items Reference to the map of items to render
             * @see renderItem()
             */
            void renderItems(const std::map<std::string, Item>& items);
            
            /**
             * @brief Renders an individual item
             * 
             * Determines the item type and dispatches to the appropriate
             * rendering method (texture or text).
             * 
             * @param key The item's unique identifier
             * @param item The item to render
             */
            void renderItem(const std::string& key, const Item& item);
            
            /**
             * @brief Renders a texture (sprite/image) item
             * 
             * Loads or retrieves the cached texture and displays it at the
             * specified position with the item's dimensions.
             * 
             * @param item The item containing texture path and positioning
             */
            void renderTexture(const Item& item);
            
            /**
             * @brief Renders a text item
             * 
             * Creates or retrieves a cached font and renders text at the
             * item's position with the specified size and color.
             * 
             * @param item The item containing text content and styling
             * @see getFontForSize()
             */
            void renderText(const Item& item);
    };
}
