/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sdl2
*/

#pragma once
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
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
    #define FONT_PATH "assets/AdwaitaMono-Regular.ttf"

namespace Arc
{
    /**
     * @class Sdl2
     * @brief Hardware-accelerated graphics renderer using SDL2
     * 
     * The Sdl2 class implements a modern graphics rendering backend using SDL2 (Simple
     * DirectMedia Layer). It provides hardware-accelerated rendering with support for
     * textures, fonts, and complex graphical elements.
     * 
     * @details
     *   - **Rendering**: Hardware-accelerated via SDL2 renderer
     *   - **Font Support**: TrueType fonts (TTF) with size caching
     *   - **Texture Support**: Image loading and caching for performance
     *   - **Cross-platform**: Works on Windows, Linux, macOS
     *   - **Performance**: Optimized with font and texture caching
     *   - **Color Support**: Full RGB color palette
     * 
     * @inherits IRenderer
     * @see IRenderer
     */
    class Sdl2 : public IRenderer
    {
        public:
            /**
             * @brief Constructs an SDL2 renderer
             * 
             * Initializes SDL2 libraries but does not yet create a window.
             * Window creation is deferred to createWindow().
             */
            Sdl2();
            
            /**
             * @brief Destructor
             * 
             * Cleans up all SDL2 resources including window, renderer,
             * cached fonts, and cached textures.
             */
            ~Sdl2() override;

            /**
             * @brief Renders all items to the SDL2 window
             * 
             * Clears the renderer, iterates through items by draw order,
             * renders each item (textures and text), and presents the result.
             * 
             * @param itemList Reference to the map of items to render
             * @see renderItems(), renderItem()
             */
            void display(std::map<std::string, Item> &itemList) override;
            
            /**
             * @brief Retrieves and processes input events from SDL2
             * 
             * Polls for SDL2 events and converts them to Event objects.
             * Handles keyboard input, mouse events, and window close events.
             * 
             * @param event Reference to the Event object to populate
             * @return true if an event was captured, false if no events pending
             */
            bool pollEvent(Event& event) override;
            
            /**
             * @brief Creates and initializes the SDL2 window
             * 
             * Creates an SDL2 window with the specified dimensions, title,
             * and initializes the renderer with hardware acceleration.
             * 
             * @param width Window width in pixels
             * @param height Window height in pixels
             * @param title Window title displayed in title bar
             * 
             * @throws AError if window or renderer creation fails
             */
            void createWindow(int width, int height, const std::string& title) override;
            
            /**
             * @brief Clears the renderer (sets background color)
             * 
             * Sets the renderer draw color to black and fills the entire
             * rendering area. Called at the start of each display frame.
             */
            void clear();

        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            TTF_Font* _font;
            std::map<int, TTF_Font*> _font_cache;
            std::map<std::string, SDL_Texture*> _texture_cache;

            /**
             * @brief Gets or loads a font for the specified size
             * 
             * Caches fonts by size to avoid repeated file I/O.
             * If the font size is already cached, returns the cached version.
             * 
             * @param size Font size in points
             * @return Pointer to TTF_Font, or nullptr if loading fails
             */
            TTF_Font* getFontForSize(int size);
            
            /**
             * @brief Gets or loads a texture from the specified file path
             * 
             * Caches textures by path to improve performance and reduce
             * redundant file loading and GPU memory allocation.
             * 
             * @param path File path to the image asset
             * @return Pointer to SDL_Texture, or nullptr if loading fails
             */
            SDL_Texture* getTextureForPath(const std::string& path);
            
            /**
             * @brief Renders all items in the item list
             * 
             * Internal method that sorts items by draw order and renders each one.
             * 
             * @param items Reference to the map of items to render
             * @see renderItem()
             */
            void renderItems(const std::map<std::string, Item>& items);
            
            /**
             * @brief Renders a single item
             * 
             * Dispatches to renderTexture() or renderText() based on item type.
             * 
             * @param key The item's identifier key
             * @param item The item to render
             */
            void renderItem(const std::string& key, const Item& item);
            
            /**
             * @brief Renders a texture item to the screen
             * 
             * Loads or retrieves a cached texture and renders it at the item's
             * specified position and size.
             * 
             * @param item The item containing texture path and position
             */
            void renderTexture(const Item& item);
            
            /**
             * @brief Renders text to the screen
             * 
             * Renders text using TTF at the specified position and size.
             * Converts text surface to texture and displays it.
             * 
             * @param item The item containing text and styling information
             * @see getFontForSize()
             */
            void renderText(const Item& item);
    };
}
