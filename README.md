*This project has been created as part of the 42 curriculum by panne-ro and mleschev.*

# Cub3D

## Description

Cub3D is a graphical project inspired by early 3D engines, notably the famous game *Wolfenstein 3D*.
The goal is to create a dynamic first-person view inside a maze using a technique called **raycasting**.

This technique consists of simulating a 3D environment while, in the background, the entire game is based on a 2D map.

The program reads a map described in a `.cub` file and generates a pseudo-3D environment where the player can move, rotate, and explore in real time. Walls are projected based on their distance, creating an illusion of depth using simple 2D calculations.

This project introduces several key concepts:

* Raycasting algorithm (the one used here is DDA — *Digital Differential Analyzer*)
* Window and image management using MiniLibX
* Event handling (keyboard inputs) using MiniLibX
* Texture mapping
* Basic game engine structure

## Instructions

### Prerequisites

* Linux (recommended)
* `cc` compiler
* `make`
* MiniLibX (provided by 42 on the project page or available [here with paris github]( https://github.com/42paris/minilibx-linux))

### Compilation

Clone the repository and compile:

```bash
git clone <repository_url> cub3d
cd cub3d
make
```

### Execution

Run the program with a valid map file:

```bash
./cub3D maps/map.cub
```

### Controls

| Key   | Action        |
| ----- | ------------- |
| W / Z | Move forward  |
| S     | Move backward |
| A     | Move left     |
| D     | Move right    |
| ← / → | Rotate camera |
| ESC   | Exit          |

## Features

* Real-time raycasting engine using DDA
* Smooth player movement
* Wall textures (North, South, East, West)
* Floor and ceiling colors
* Map parsing and validation
* Window management with MiniLibX
* Basic error handling

## Map Format

A valid `.cub` file must contain:

* Texture paths for each wall (NO, SO, WE, EA)
* Floor (`F`) and ceiling (`C`) colors
* A map using:

  * `1` for walls
  * `0` for empty spaces
  * `N`, `S`, `E`, `W` for the player’s starting position

Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

## Technical Choices

* Language: C
* Graphics library: MiniLibX
* Rendering: Raycasting (DDA algorithm)
* Memory management: Manual (`malloc` / `free`)

## Resources

### Documentation & Tutorials

* [MiniLibX documentation (community resource)](https://github.com/Flmjm/aled_la_mlx/tree/main)
* [Lode’s Computer Graphics Tutorial (raycasting)](https://lodev.org/cgtutor/raycasting.html)
* [3DSage YouTube tutorial (C++)](https://www.youtube.com/watch?v=gYRrGTC7GtA&t=392s)
* [42 Cub3D subject](https://projects.intra.42.fr/projects/cub3d)
### AI Usage

AI tools (including ChatGPT) were used for:

* Understanding raycasting and fixing logic issues
* Explaining errors (segmentation faults, memory management)
* Improving code structure and readability
* Handling edge cases in parsing
* Writing and structuring this README

All code, and more generally everything produced with the help of AI, was reviewed, understood, and manually integrated to comply with 42 requirements.

#### Possible Improvements

* Mouse support for camera rotation
* Sprite rendering (enemies, objects)
* Minimap
* Doors and interactive elements
* Sound integration

## Authors

* panne-ro
* mleschev

---
