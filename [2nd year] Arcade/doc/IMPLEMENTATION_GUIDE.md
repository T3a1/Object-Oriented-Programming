# Implementation Guide: Creating Games and Renderers for Arcade

This document provides a comprehensive guide for implementing new game libraries or graphics renderers compatible with the Arcade system.

## Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [Implementing a Game](#implementing-a-game)
3. [Implementing a Renderer](#implementing-a-renderer)
4. [Dynamic Library Requirements](#dynamic-library-requirements)
5. [Project Structure](#project-structure)
6. [Building and Testing](#building-and-testing)
7. [Troubleshooting](#troubleshooting)

## Architecture Overview

The Arcade system uses a **plugin architecture** where games and renderers are dynamically loaded at runtime as shared libraries (.so files).

### Core Components

```
┌─────────────────────────────────────────────────────────────┐
│                      Arcade Core                            │
├─────────────────────────────────────────────────────────────┤
│   - Library Discovery & Validation                          │
│   - Plugin Loading (DLloader)                               │
│   - Menu & Game Switching                                   │
│   - Event Loop Management                                   │
└─────────┬─────────────────────────────────────┬─────────────┘
          │                                     │
     ┌────▼────┐                         ┌──────▼──────┐
     │   IGame │                         │ IRenderer   │
     └────┬────┘                         └──────┬──────┘
          │                                     │
    ┌─────▼──────┐                    ┌────────▼────────┐
    │   Games    │                    │    Renderers    │
    │   (.so)    │                    │     (.so)       │
    └────────────┘                    └─────────────────┘
```

### Key Design Principles

1. **Interface Segregation** - Games and renderers interact only through their interfaces
2. **Dependency Injection** - Items map passed to constructors
3. **Dynamic Discovery** - Libraries discovered from lib/ directory
4. **No Dynamic Casting** - Type-safe through templates
5. **Minimal Coupling** - Implementations are independent

## Implementing a Game

### Step 1: Create Project Structure

```
src/Game/YourGame/
├── YourGame.hpp
├── YourGame.cpp
├── CMakeLists.txt
└── (optional) assets/
```

### Step 2: Implement the IGame Interface

Create a header file `YourGame.hpp`:

```cpp
#pragma once

#include "IGame.hpp"
#include <vector>
#include <map>
#include <string>

namespace Arc
{
    /**
     * @class YourGame
     * @brief Your game implementation.
     * 
     * Inherits from IGame and implements the required methods.
     */
    class YourGame : public IGame
    {
        public:
            /**
             * @brief Constructor for YourGame.
             * @param items Reference to the items map
             */
            YourGame(std::map<std::string, Item>& items);

            /**
             * @brief Destructor.
             */
            ~YourGame();

            /**
             * @brief Updates game state based on events.
             * @param event The event to process
             */
            void update(Event event) override;

            /**
             * @brief Handles keyboard input.
             * @param event The keyboard event
             */
            void handleKey(Event event) override;

            /**
             * @brief Gets the current score.
             * @return Vector of scores
             */
            std::vector<int> getScore() const override;

            /**
             * @brief Checks if game is over.
             * @return true if game over, false otherwise
             */
            bool isGameOver() const override;

        private:
            std::map<std::string, Item>& _items;
            bool _gameOver;
            int _score;
            // Add your game state variables here
    };
}
```

### Step 3: Implement Methods in YourGame.cpp

```cpp
#include "YourGame.hpp"

namespace Arc
{
    YourGame::YourGame(std::map<std::string, Item>& items)
        : _items(items), _gameOver(false), _score(0)
    {
        // Initialize your game
        // Create initial items in _items map
        Item startItem;
        startItem.position = {100.0f, 100.0f};
        startItem.size = {50.0f, 50.0f};
        startItem.texturePath = "path/to/texture.png";
        startItem.drawOrder = 1;
        _items["player"] = startItem;
    }

    YourGame::~YourGame()
    {
        // Cleanup
    }

    void YourGame::update(Event event)
    {
        // Update game state each frame
        // Modify _items positions, states, etc.
    }

    void YourGame::handleKey(Event event)
    {
        if (event.type == Arc::Type::KeyPressed) {
            switch (event.code) {
                case Arc::Key::Left:
                    // Handle left movement
                    break;
                case Arc::Key::Right:
                    // Handle right movement
                    break;
                case Arc::Key::Escape:
                    _gameOver = true;
                    break;
                default:
                    break;
            }
        } else if (event.type == Arc::Type::Quit) {
            _gameOver = true;
        }
    }

    std::vector<int> YourGame::getScore() const
    {
        return {_score};
    }

    bool YourGame::isGameOver() const
    {
        return _gameOver;
    }
}

// REQUIRED: C-linkage entry point function
extern "C" Arc::IGame* entryPoint(std::map<std::string, Arc::Item>& items)
{
    return new Arc::YourGame(items);
}

// REQUIRED: Library type function
extern "C" int getLibraryType()
{
    return (int)Arc::LibraryType::Game;
}

// REQUIRED: Library name function
extern "C" std::string getName()
{
    return "YourGameName";
}
```

### Step 4: Create CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

project(Arc_YourGame)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories("${CMAKE_SOURCE_DIR}/src/Include")

# Source files
set(SOURCES
    YourGame.cpp
)

# Create shared library
add_library(arcade_yourgame SHARED ${SOURCES})

# Set output directory
set_target_properties(arcade_yourgame PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
    SUFFIX ".so"
)
```

### Step 5: Add to Main CMakeLists.txt

In the main `CMakeLists.txt`:

```cmake
add_subdirectory(src/Game/YourGame)
```

## Implementing a Renderer

### Step 1: Create Project Structure

```
src/Renderer/YourRenderer/
├── YourRenderer.hpp
├── YourRenderer.cpp
├── CMakeLists.txt
└── (optional) shaders/
```

### Step 2: Implement the IRenderer Interface

Create `YourRenderer.hpp`:

```cpp
#pragma once

#include "IRenderer.hpp"
#include <map>
#include <string>
#include <vector>

namespace Arc
{
    /**
     * @class YourRenderer
     * @brief Your graphics renderer implementation.
     * 
     * Inherits from IRenderer and handles all rendering operations.
     */
    class YourRenderer : public IRenderer
    {
        public:
            /**
             * @brief Constructor for YourRenderer.
             * @param items Reference to items map
             */
            YourRenderer(std::map<std::string, Item>& items);

            /**
             * @brief Destructor.
             */
            ~YourRenderer();

            /**
             * @brief Creates the display window.
             * @param width Window width in pixels
             * @param height Window height in pixels
             * @param title Window title
             */
            void createWindow(int width, int height, const std::string& title) override;

            /**
             * @brief Renders all items to the display.
             * @param items Map of named items to render
             */
            void display(std::map<std::string, Item>& items) override;

            /**
             * @brief Polls for user input events.
             * @param event Output parameter for event data
             * @return true if event received, false if queue empty
             */
            bool pollEvent(Event& event) override;

        private:
            std::map<std::string, Item>& _items;
            bool _windowOpen;
            // Add your renderer state here
            
            /**
             * @brief Renders a single item.
             * @param item The item to render
             */
            void renderItem(const Item& item);

            /**
             * @brief Converts key codes from renderer to Arc::Key format.
             * @param rendererKey The native key code
             * @return Corresponding Arc::Key
             */
            Arc::Key convertKeyCode(int rendererKey);
    };
}
```

### Step 3: Implement Methods in YourRenderer.cpp

```cpp
#include "YourRenderer.hpp"
#include <iostream>

namespace Arc
{
    YourRenderer::YourRenderer(std::map<std::string, Item>& items)
        : _items(items), _windowOpen(false)
    {
    }

    YourRenderer::~YourRenderer()
    {
        // Cleanup graphics resources
    }

    void YourRenderer::createWindow(int width, int height, const std::string& title)
    {
        // Initialize your graphics library
        // Create window with specified dimensions and title
        _windowOpen = true;
    }

    void YourRenderer::display(std::map<std::string, Item>& items)
    {
        // Clear screen
        // For each item in items map, call renderItem()
        // Update display (flip buffers, refresh, etc.)
        
        for (auto& [name, item] : items) {
            renderItem(item);
        }
    }

    bool YourRenderer::pollEvent(Event& event)
    {
        // Poll for input events from your graphics library
        // Convert native events to Arc::Event format
        // Return true if event found, false otherwise
        
        // Example (pseudocode):
        // if (nativeInputQueue.empty())
        //     return false;
        // 
        // NativeEvent nativeEvent = nativeInputQueue.pop();
        // event.type = nativeEvent.type == NATIVE_KEY ?
        //              Arc::Type::KeyPressed : Arc::Type::Quit;
        // event.code = convertKeyCode(nativeEvent.code);
        // event.mouse.x = nativeEvent.mouseX;
        // event.mouse.y = nativeEvent.mouseY;
        // 
        // return true;
        
        return false;
    }

    void YourRenderer::renderItem(const Item& item)
    {
        // Render one item based on its properties:
        // - Position: item.position
        // - Size: item.size
        // - Rotation: item.rotation
        // - Texture: item.texturePath (load and cache if needed)
        // - Text: item.text (render text if present)
        // - DrawOrder: item.drawOrder (render in order, highest on top)
        // - IsHovered: item.isHovered (highlight if needed)
    }

    Arc::Key YourRenderer::convertKeyCode(int rendererKey)
    {
        // Convert your graphics library's key codes to Arc::Key
        // Example:
        // switch(rendererKey) {
        //     case NATIVE_KEY_A: return Arc::Key::A;
        //     case NATIVE_KEY_LEFT: return Arc::Key::Left;
        //     // ... etc
        // }
        return Arc::Key::None;
    }
}

// REQUIRED: C-linkage entry point
extern "C" Arc::IRenderer* entryPoint(std::map<std::string, Arc::Item>& items)
{
    return new Arc::YourRenderer(items);
}

// REQUIRED: Library type function
extern "C" int getLibraryType()
{
    return (int)Arc::LibraryType::Renderer;
}

// REQUIRED: Library name function
extern "C" std::string getName()
{
    return "YourRendererName";
}
```

### Step 4: Create CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

project(Arc_YourRenderer)

set(CMAKE_CXX_STANDARD 17)

include_directories("${CMAKE_SOURCE_DIR}/src/Include")

# Link your graphics library here
# Example for SDL2:
# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
    YourRenderer.cpp
)

add_library(arcade_yourrenderer SHARED ${SOURCES})

# Link libraries
# target_link_libraries(arcade_yourrenderer ${SDL2_LIBRARIES})

set_target_properties(arcade_yourrenderer PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
    SUFFIX ".so"
)
```

### Step 5: Add to Main CMakeLists.txt

```cmake
add_subdirectory(src/Renderer/YourRenderer)
```

## Dynamic Library Requirements

Every game and renderer library must export exactly three C-linkage functions:

### 1. Entry Point Function

```cpp
extern "C" T* entryPoint(std::map<std::string, Arc::Item>& items)
{
    return new YourImplementation(items);
}
```

**Requirements:**
- Must be named exactly `entryPoint`
- Returns pointer to new instance
- Takes reference to items map
- Called immediately after dlopen

### 2. Library Type Function

```cpp
extern "C" int getLibraryType()
{
    return (int)Arc::LibraryType::Game;  // or Renderer
}
```

**Requirements:**
- Must be named exactly `getLibraryType`
- Returns 0 for Game, 1 for Renderer
- Used during library discovery

### 3. Library Name Function

```cpp
extern "C" std::string getName()
{
    return "MyGameName";
}
```

**Requirements:**
- Must be named exactly `getName`
- Returns human-readable library name
- Displayed in menus

### Symbol Export Notes

- Use `extern "C"` to prevent name mangling
- Compiler must not mangle these symbols
- Use `nm -D libname.so` to verify symbols are exported
- Check with `dlsym()` if symbols are accessible

## Project Structure

### Typical Game/Renderer Layout

```
src/Game/Snake/
├── CMakeLists.txt           # Defines build rules for this library
├── Snake.hpp                # Public interface
├── Snake.cpp                # Implementation
└── (optional) assets/
    ├── snake_head.png
    └── food.png

src/Renderer/SDL2/
├── CMakeLists.txt
├── Sdl2.hpp
├── Sdl2.cpp
└── (optional) shaders/
    ├── vertex.glsl
    └── fragment.glsl
```

### File Naming Conventions

- Header: `ClassName.hpp`
- Implementation: `ClassName.cpp`
- Output library: `lib/arcade_classname.so`

## Building and Testing

### Build Individual Library

```bash
cd build
cmake ..
make arcade_yourgame
```

### Verify Library Export

Check exported symbols:
```bash
nm -D lib/arcade_yourgame.so | grep entryPoint
```

Should output:
```
0000000000001234 T entryPoint
```

### Test Loading

Create a small test program:
```cpp
#include <dlfcn.h>
#include <iostream>
#include <map>

#include "IGame.hpp"
#include "Utils.hpp"

int main() {
    void* handle = dlopen("./lib/arcade_yourgame.so", RTLD_LAZY);
    
    auto entryPoint = (Arc::IGame*(*)(std::map<std::string, Arc::Item>&))
        dlsym(handle, "entryPoint");
    
    if (!entryPoint) {
        std::cerr << "Failed to load: " << dlerror() << std::endl;
        return 1;
    }
    
    std::map<std::string, Arc::Item> items;
    Arc::IGame* game = entryPoint(items);
    
    if (!game) {
        std::cerr << "Failed to create instance" << std::endl;
        return 1;
    }
    
    std::cout << "Success!" << std::endl;
    delete game;
    dlclose(handle);
    return 0;
}
```

### Test with Arcade Launcher

```bash
./arcade ./lib/arcade_ncurses.so
```

Your game should appear in the menu and be selectable.

## Troubleshooting

### Common Issues

**Problem**: Library not appearing in menu

**Solutions**:
- Check `getName()` returns non-empty string
- Verify `getLibraryType()` returns correct value
- Use `nm` to check symbols are exported
- Ensure library is in `lib/` directory with `.so` extension

---

**Problem**: Segmentation fault when loading

**Solutions**:
- Check `entryPoint()` doesn't crash with null items
- Verify all memory allocations
- Use debugger: `gdb --args ./arcade ./lib/...`
- Check constructors don't throw exceptions

---

**Problem**: Items not rendering

**Solutions**:
- Populate items map in game constructor
- Verify positions are within window bounds
- Check texture paths are relative to executable or absolute
- Debug with small test items first

---

**Problem**: Input not working

**Solutions**:
- Check `pollEvent()` correctly converts key codes
- Verify event handling logic in game
- Test key mapping with simple debug output
- Check mouse position is being populated

---

**Problem**: Linker errors with undefined references

**Solutions**:
- Add `-fPIC` flag for position-independent code
- Link with required libraries in CMakeLists.txt
- Check all dependencies are installed
- Use `ldd` to check library dependencies: `ldd lib/arcade_game.so`

## Advanced Topics

### Thread Safety

- Do not use global state
- Each instance gets its own items map
- Thread-local storage if needed for library resources

### Performance Considerations

- Cache loaded textures/resources
- Use `drawOrder` to minimize rendering
- Consider dirty rectangle updating
- Profile with `perf` or `valgrind`

### Asset Loading

- Store assets relative to executable or in absolute paths
- Use resource loading utilities
- Handle missing assets gracefully
- Consider embedded resources for small assets

---

**Last Updated**: 2026-04-11
