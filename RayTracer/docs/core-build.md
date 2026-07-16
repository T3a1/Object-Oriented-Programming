# Core Build

The project is built with CMake and produces three main outputs:

- `raytracer_core`, a shared library containing the renderer core
- `raytracer`, the executable launched from the repository root
- plugin shared libraries in `plugins/`

## Build Layout

The root `CMakeLists.txt` defines the complete build:

- the project uses C++17
- compiler warnings are enabled with `-Wall -Wextra`
- include paths are set for the source tree and plugin helpers
- the core library links against `config++` and `dl`
- the executable also links against `raytracer_core`, `config++`, and `dl`

## Build From Root

From the repository root, the usual CMake build flow is:

```bash
cmake -S . -B build
cmake --build build
```

## Core Library

The core library is assembled from the rendering and scene code under `src/`:

- math types such as vectors, points, and rotations
- ray and camera logic
- scene management and scene building
- shapes, factories, lights, and utility helpers

At build time, CMake places the shared library output in `plugins/`.

## Plugins

Two plugin libraries are built alongside the core:

- `libprimitives.so`
- `liblights.so`

They are also written to `plugins/` and loaded by the application at runtime.
