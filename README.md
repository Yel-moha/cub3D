# cub3D

`cub3D` is a 42 raycasting project inspired by Wolfenstein 3D. This repository contains a complete parser, validation layer, rendering engine, doors, minimap, and animated monitor sprites.

## Overview

The program starts from a `.cub` scene file and goes through these stages:

1. Parse the configuration section.
2. Validate the map and its borders.
3. Build the runtime scene state.
4. Initialize MiniLibX, textures, player state, and render buffers.
5. Run the frame loop: input, raycasting, walls, sprites, minimap, and buffer swap.

## Parsing Flow

The parsing pipeline is centered in `src/parsing/parse_line.c`.

### 1. Read the input file line by line

`get_next_line()` reads the scene file progressively. The parser first scans the file to collect metadata and map dimensions.

### 2. Parse textures and colors

The following identifiers are handled:

- `NO`, `SO`, `WE`, `EA` for wall textures
- `F` for floor color
- `C` for ceiling color

Texture paths are stored in the scene structure and later loaded by the engine.

### 3. Detect the map section

When the parser reaches the map, it checks that only valid symbols are present.

Supported map tokens include:

- `1` wall
- `0` empty floor
- `N`, `S`, `E`, `W` player spawn and facing direction
- `D` door tile
- `O` open-door tile used internally at render/debug time
- `M` animated monitor sprite
- space as padding / outside-map buffer

### 4. Validate the map

Before the engine starts, the map is checked for:

- closed borders
- exactly one player spawn
- no invalid holes in the playable area
- consistent rows and dimensions

This validation prevents the raycaster from reading outside the map.

### 5. Build the grid

Once valid, the map is copied into an internal grid representation. The engine uses this grid for collisions, ray traversal, doors, and sprite placement.

## Engine Flow

The engine entry point is `src/engine/engine.c`.

### 1. Initialize runtime data

The engine allocates:

- the ray array
- the z-buffer for sprites
- the door state matrix
- the sprite list extracted from `M` tiles

### 2. Create the window and main image buffer

MiniLibX creates the window and the off-screen image used as the frame buffer.

### 3. Load textures

The engine loads:

- 4 wall textures
- 1 door texture
- 4 animated monitor frames

If a texture fails to load, the program exits cleanly.

### 4. Initialize the player

The player position is centered on the spawn tile and the direction vector is set according to the spawn symbol:

- `N` north
- `S` south
- `E` east
- `W` west

### 5. Enter the frame loop

Each frame does:

1. Handle keys and mouse input.
2. Draw ceiling and floor.
3. Cast one ray per screen column.
4. Run DDA to find the first blocking tile.
5. Draw the wall column with the correct texture.
6. Draw sprites using the z-buffer.
7. Draw minimap/debug overlays.
8. Present the final image with `mlx_put_image_to_window()`.

## Rendering Details

### Raycasting

The engine uses the player direction and camera plane to build one ray per column. DDA walks the grid until it finds a wall or a closed door.

### Doors

Doors are stored in a separate `door_open` matrix.

- Closed doors behave like solid walls.
- Open doors do not block movement or rays.
- Pressing `E` toggles the closest door.

### Sprites

Sprites are world objects stored as `M` in the map.

- They are collected during engine initialization.
- They are sorted by distance before rendering.
- They are projected with the same camera basis used for raycasting.
- A z-buffer prevents sprites from drawing over closer walls.
- The monitor sprite animates by cycling through 4 texture frames.

## Project Structure

- `src/parsing/` - file parsing, validation, and scene setup
- `src/engine/` - raycasting, movement, textures, doors, sprites, and rendering
- `textures/` - runtime image assets used by the engine
- `map/` - sample and test `.cub` scenes
- `docs/ENGINE.md` - technical notes about the engine math and flow

## Build

```bash
make
```

To rebuild from scratch:

```bash
make fclean && make
```

## Run

```bash
./cub3d map/valid_closed_small.cub
```

Other useful test scenes are in `map/`.

## Notes

- The project is designed to exit cleanly on parsing or loading failures.
- Valgrind checks on valid and invalid test maps are clean in the current state.
- The animated monitor sprite uses the `M` tile symbol so it can be placed directly in the map.
