# so_long

so_long is a project from the 42 core curriculum that involves developing a simple 2D top-down game. Written entirely in C, it introduces graphical window management, event handling (keyboard and mouse hooks), texture mapping, and map parsing using the MiniLibX library.

## Table of Contents

- [Project Description](#project-description)
- [Game Rules](#game-rules)
- [Map Requirements](#map-requirements)
- [Compilation and Execution](#compilation-and-execution)
- [Controls](#controls)
- [Memory Management](#memory-management)

## Project Description

The objective of `so_long` is to navigate a character through a map, collect all items present on the grid, and escape through an exit. The project serves as an introduction to basic graphics rendering, real-time input loop execution, and valid map verification using parsing algorithms (such as flood fill).

## Game Rules

- The player must collect all available collectible items on the map before reaching the exit.
- Every successful step made by the player must be tracked and printed directly inside the shell terminal.
- The game loop runs in real-time and must close cleanly whenever the exit conditions or window escape triggers are called.

## Map Requirements

The program reads map configurations from files ending with the `.ber` extension. The map grid is constructed using the following specific characters:

- `0` : Empty space / Ground
- `1` : Wall / Obstacle
- `C` : Collectible item
- `E` : Map exit
- `P` : Player starting position

### Parsing Constraints
- The map configuration must be a perfect rectangle completely enclosed by walls (`1`).
- The file must contain exactly one player starting location (`P`), at least one exit (`E`), and at least one collectible (`C`).
- The code must implement a pathfinding check to ensure that the exit and all collectibles are structurally reachable by the player.

## Compilation and Execution

### Prerequisites

To compile and run this project, you need standard development tools (`gcc`, `make`) along with the X11 graphics system headers installed on your operating system.

### Compilation

Compile the main project executable using the root Makefile:

```bash
make
