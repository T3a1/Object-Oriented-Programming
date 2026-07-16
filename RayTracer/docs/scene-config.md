# Scene Configuration

The scene file is a `libconfig` configuration file with the `.cfg` extension. The parser is implemented in `src/Raytracer/SceneBuilding/LibConfigSceneBuilder.cpp` and reads the scene in four main sections:

- `camera`
- `groups`
- `primitives`
- `lights`

## Camera

The `camera` section configures the render target and viewport:

- `resolution.width` and `resolution.height`
- `background_color.r`, `background_color.g`, `background_color.b`
- optional `background_color.a`
- `fov`
- `cam_origin`
- `viewport_origin`
- `bottom_side`
- `left_side`

Example:

```cfg
camera: {
    resolution = { width = 1900; height = 1080; };
    background_color = { r = 0.0; g = 0.0; b = 0.0; };
    fov = 60.0;
    cam_origin = { x = 0.0; y = 1.5; z = 0.0; };
    viewport_origin = { x = -4.0; y = 0.5; z = 8.0; };
    bottom_side = { x = 8.0; y = 0.0; };
    left_side = { x = 0.0; y = 8.0; };
};
```

## Primitives

The `primitives` section is an array of shapes. Each primitive needs:

- `type`
- `color`
- `texture_filename`
- `settings`

Supported primitive types in the parser:

- `sphere`
- `plane`
- `cylinder`
- `cone`
- `limitedCylinder`
- `limitedCone`
- `triangle`
- `obj`

Common shape settings:

- `sphere`: `origin`, `radius`
- `plane`: `origin`, `direction`
- `cylinder`: `origin`, `direction`, `radius`
- `cone`: `origin`, `direction`, `radius`
- `limitedCylinder`: `origin`, `direction`, `radius`, `height`
- `limitedCone`: `origin`, `direction`, `radius`, `height`
- `triangle`: `a`, `b`, `c`
- `obj`: `file`, optional `mtl`, optional `reference_point`, optional `scale`, optional `rotateX`, `rotateY`, `rotateZ`, optional `translate`

If `texture_filename` is present and not empty, it is attached to the shape.

## Groups

The `groups` section lets you bundle shapes under a named group:

- each group has a `name`
- each group has a `shapes` array
- shapes inside a group use the same format as `primitives`

Groups are built as `GroupShape` instances and can be used to organize multiple shapes together.

## Texture From File

A texture can be applied to every group / primitive shape using `texture_filename`

The texture file MUST be a `.ppm` extension

Example:

    texture_filename = "image.ppm"

To convert a PNG / JPG, use the command:

`convert image.png image.ppm`

## Lights

The `lights` section is split into:

- `ambient`
- `directional`
- `point`

Ambient light uses `intensity` and `color`.

Directional and point lights are defined as arrays of objects, each with its own intensity and position/direction fields.

## Behavior Notes

- Missing sections are handled by the builder with error messages.
- Invalid primitive types are reported as `Unknown primitive type`.
- OBJ shapes can be loaded with or without an `.mtl` file.
- When `reference_point` and transformation fields are present, they are applied during object setup.
