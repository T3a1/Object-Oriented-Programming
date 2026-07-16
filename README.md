# Object-Oriented Programming

A collection of technical projects built as part of the Object-Oriented Programming curriculum at Epitech. Each subfolder is a standalone project exploring different OOP concepts — interfaces, plugin architectures, design patterns, dynamic library loading, and 3D math — implemented in C++.

## Domain Overview

Object-oriented programming, as covered by these projects, focuses on structuring software around interacting objects rather than raw procedures: encapsulation, inheritance, polymorphism, and composition. In practice here, that means:

- **Interface-driven design** — defining abstract contracts (`IGame`, `IRenderer`, `IShape`, `ILight`) that concrete implementations must satisfy, so components can be swapped without touching the code that uses them.
- **Plugin architectures** — loading implementations of those interfaces from shared libraries at runtime (`dlopen`/`dlsym`), so new games, renderers, shapes, or lights can be added without recompiling the core.
- **Design patterns** — Factory, Builder, Strategy, and Template Method patterns used to keep object creation and behavior extensible and decoupled.
- **Applied 3D math and systems programming** — vectors, rays, geometric intersection, and low-level resource management (dynamic libraries, file watching, graphics backends) underpinning the higher-level OOP structure.

## Projects

### [`[2nd year] Arcade`](./%5B2nd%20year%5D%20Arcade/)

An extensible game launcher built around a plugin architecture. Games and renderers are compiled as separate shared libraries and loaded dynamically at runtime, so new games (Snake, Minesweeper) or renderer backends (Ncurses, SDL2, SFML) can be added without recompiling the core launcher. Demonstrates interface-based design (`IGame`, `IRenderer`), a type-safe dynamic library loader, and a custom exception hierarchy for error handling.

### [`[2nd year] RayTracer`](./%5B2nd%20year%5D%20RayTracer/)

An object-oriented ray tracing renderer that simulates light rays through a 3D scene to produce photorealistic images. Scenes (cameras, shapes, lights) are described in `.cfg` files and constructed via the Builder pattern, with shapes and lights themselves loadable as runtime plugins. Covers geometric primitives, BVH-accelerated intersection, shadow casting, and multiple lighting models.

## Common Threads

Both projects, despite differing in domain (game launching vs. rendering), share the same underlying architectural approach:

- A small set of core interfaces define what a component must do.
- Concrete implementations live behind those interfaces and are interchangeable.
- Runtime plugin loading (via `dlopen`) is used to extend functionality without modifying or recompiling the core.
- Object creation is centralized through factories or builders rather than scattered `new` calls.

## License

MIT License — see [`LICENSE`](./LICENSE). Copyright (c) 2026 Léandre Fouret.
