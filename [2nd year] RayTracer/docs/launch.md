# Launching the Project

The executable is produced at the repository root as `./raytracer`.

## Basic Launch

Run the renderer from the project root with a scene file:

```bash
./raytracer scenes/scene.cfg
```

## Options

- `--help` displays the usage message
- `-a <int>` sets the anti-aliasing iteration count
- `--hardcoded` ignores the scene file and renders the built-in test scene

Example with anti-aliasing:

```bash
./raytracer scenes/scene.cfg -a 10
```

Example using the built-in scene:

```bash
./raytracer --hardcoded
```

## Build Then Run

If the project has not been built yet, run the root build commands first:

```bash
cmake -S . -B build
cmake --build build
```

Then launch `./raytracer` from the repository root.
