*This project has been created as part of the 42 curriculum by phofer, thchau.*

# cub3D

## Description

cub3D is a 3D maze explorer built from scratch in C using the raycasting technique pioneered by games like Wolfenstein 3D. The engine renders a first-person perspective view of a maze defined by a `.cub` scene file, complete with directional wall textures, floor and ceiling colors, smooth mouse-driven camera control, and a live minimap overlay.

The goal of the project is to deepen understanding of linear algebra, trigonometry, and low-level graphics programming — building a real-time renderer without any 3D graphics library, using only miniLibX for window and image management.

## Features

- Raycasting engine with four directional wall textures (N/S/E/W)
- Textured walls sampled from `.xpm` image files
- Configurable floor and ceiling colors via the scene file
- Smooth WASD movement with per-axis wall collision and sliding
- Mouse look with hidden cursor
- Arrow key rotation as fallback
- Player-centered minimap with FOV wedge indicator
- Scene description parsed from a `.cub` file

## Instructions

### Requirements

- Linux or macOS
- `gcc`, `make`
- miniLibX (included)
- libft (included)

### Compilation

```bash
make
```

To remove object files:
```bash
make clean
```

To remove all build artifacts including the binary:
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Execution

```bash
./cub3D path/to/scene.cub
```

### Scene file format

The `.cub` file must define four textures, floor/ceiling colors, and a map:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

1111111
1000001
100N001
1000001
1111111
```

Map rules:
- `1` = wall, `0` = empty space
- `N`, `S`, `E`, `W` = player spawn with facing direction
- The map must be fully enclosed by walls
- The map must be the last element in the file

### Controls

| Key | Action |
|---|---|
| W / A / S / D | Move forward / left / back / right |
| ← / → | Rotate left / right |
| Mouse | Look left / right |
| ESC | Quit |

## Resources

### Raycasting

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for the DDA raycasting algorithm and texture mapping
- [Raycasting — Wikipedia](https://en.wikipedia.org/wiki/Ray_casting)

### miniLibX

- [miniLibX documentation (harm-smits)](https://harm-smits.github.io/42docs/libs/minilibx)
- [miniLibX Linux source](https://github.com/42Paris/minilibx-linux)

### AI

Claude (Anthropic) was used as a research and guidance tool throughout the project — to understand raycasting concepts, explore implementation approaches, and reason through bugs.
