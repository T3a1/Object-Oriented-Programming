# Arcade - Extensible Game Launcher

An extensible game launcher system built with object-oriented C++ principles, demonstrating advanced concepts like dynamic library loading, interface-based design, and plugin architecture.

## Project Overview

Arcade is a modular game launcher that allows:
- **Dynamic game loading** - Add games by placing .so files in the `lib/` directory
- **Multiple renderer support** - Switch between different graphics libraries at runtime (Ncurses, SDL2, SFML)
- **Plugin-based architecture** - No recompilation needed to add new games or renderers
- **Unified interface** - Single menu for game selection and renderer switching

## Key Features

- Plugin-based game and renderer system
- Dynamic library loading using dlopen/dlsym
- Interface-based design (IGame, IRenderer)
- Score tracking and high score management
- Multi-renderer support
- Type-safe template-based loader (DLloader)

## Project Structure

```
├── src/
│   ├── main.cpp                 # Entry point
│   ├── Core/                    # Core engine
│   │   ├── Core.cpp
│   │   └── Core.hpp
│   ├── Include/                 # System interfaces and utilities
│   │   ├── IGame.hpp            # Game interface
│   │   ├── IRenderer.hpp        # Renderer interface
│   │   ├── Event.hpp            # Input event structure
│   │   ├── Utils.hpp            # Utility structures (Item, LibraryType)
│   │   ├── ArcError.hpp         # Exception hierarchy
│   │   └── DLloader.hpp         # Dynamic library loader template
│   ├── Game/                    # Game implementations
│   │   ├── Menu/
│   │   ├── Snake/
│   │   └── Minesweeper/
│   └── Renderer/                # Renderer implementations
│       ├── Ncurses/
│       ├── Sdl2/
│       └── Sfml/
├── CMakeLists.txt               # Build configuration
├── Doxyfile                     # Doxygen configuration
├── README.md                    # This file
├── CONTRIBUTORS.md              # Project contributors and collaboration info
├── doc/                         # Documentation
│   ├── IMPLEMENTATION_GUIDE.md  # How to implement new games/renderers
│   ├── ARCHITECTURE.md          # System architecture explanation
│   ├── CLASS_DIAGRAM.md         # UML class diagram
│   └── INTERFACE_AGREEMENT.md   # Interface collaboration agreement
├── lib/                         # Compiled libraries
└── assets/                      # Game assets
```

## Building

### Prerequisites

- CMake >= 3.10
- C++17 compatible compiler
- Optional dependencies:
  - libncurses-dev (for Ncurses renderer)
  - libsdl2-dev (for SDL2 renderer)
  - libsfml-dev (for SFML renderer)
  - doxygen (for documentation generation)

### Compilation

```bash
mkdir build
cd build
cmake ..
make
```

### Running

```bash
./arcade ./lib/arcade_ncurses.so
```

## Interfaces

The Arcade system is built around two main interfaces:

### IGame
Games must implement this interface and export:
- `void update(Event event)` - Update game state
- `void handleKey(Event event)` - Handle keyboard input
- `std::vector<int> getScore() const` - Get score
- `bool isGameOver() const` - Check game status

### IRenderer
Renderers must implement this interface and export:
- `void display(std::map<std::string, Item>& items)` - Render items
- `void createWindow(int width, int height, const std::string& title)` - Create window
- `bool pollEvent(Event& event)` - Poll for input events

All libraries must also export:
- `extern "C" T* entryPoint(std::map<std::string, Item>&)` - Factory function
- `extern "C" int getLibraryType()` - Return library type
- `extern "C" std::string getName()` - Return library name

## Available Games

- **Snake** - Classic snake game
- **Minesweeper** - Minesweeper puzzle game

## Available Renderers

- **Ncurses** - Terminal-based rendering
- **SDL2** - 2D graphics library
- **SFML** - Simple and Fast Multimedia Library

## Documentation

### Generated Documentation

Generate HTML/LaTeX documentation with Doxygen:
```bash
doxygen Doxyfile
```

The generated documentation will include detailed API documentation for all interfaces and classes.

### Manual Documentation

- **[IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md)** - Step-by-step guide for implementing new games or renderers

## Interface Collaboration

This project participates in interface collaboration with external groups to ensure cross-compatibility:

- **Group Collaborator Contact**: eliott1.duchene@epitech.eu
- **Interface Version**: 1.0
- **Collaboration Details**: See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md)

Through this collaboration, external teams can:
- Use our renderers with their game implementations
- Use our game implementations with their renderers
- Share their games and renderers with the Arcade launcher

## Error Handling

The system uses a custom exception hierarchy:

- `AError` - Base exception
- `ErrorMinor` - Recoverable errors
- `ErrorMajor` - Significant errors
- `ErrorCritical` - Fatal errors (exit code 84)
- `Miscellaneous` - Uncategorized errors

## Development

### Adding a New Game

1. See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md) for detailed instructions
2. Implement IGame interface
3. Export required C functions
4. Place compiled .so in lib/ directory
5. Library is automatically discovered

### Adding a New Renderer

1. See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md) for detailed instructions
2. Implement IRenderer interface
3. Export required C functions
4. Place compiled .so in lib/ directory
5. Available immediately in game launcher

## Dependencies

- **libdl** - Dynamic linking library (system)
- **ncurses** - Terminal rendering (optional)
- **SDL2** - 2D graphics (optional)
- **SFML** - Multimedia library (optional)

## License

EPITECH PROJECT, 2026

## Contact & Collaboration

For questions about interface collaboration or technical integration, see [CONTRIBUTORS.md](CONTRIBUTORS.md).
