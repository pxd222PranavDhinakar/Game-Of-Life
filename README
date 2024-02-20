# Conway's Game of Life

## Description

This project is an implementation of Conway's Game of Life, a cellular automaton devised by the British mathematician John Horton Conway in 1970. The game is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input. It consists of a grid of cells which, based on a few mathematical rules, can live, die, or multiply. Depending on the initial conditions, the cells form various patterns throughout the course of the game.

## Installation

```bash
git clone https://github.com/pxd222PranavDhinakar/game-of-life.git
cd game-of-life
```

Replace `https://github.com/yourusername/game-of-life.git` with the actual URL of your repository.

## Usage

Before running the game, please ensure that you have the following prerequisites installed on your system:

- **GCC Compiler**: Needed to compile the C code.
- **SDL2**: A cross-platform development library designed to provide low-level access to audio, video, and graphics hardware via OpenGL and Direct3D.
- **make**: A build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles.

### Installing Prerequisites

#### On Ubuntu/Debian-based systems:

```bash
sudo apt-get update
sudo apt-get install gcc libsdl2-dev make
```

#### On Fedora/Red Hat-based systems:

```bash
sudo dnf update
sudo dnf install gcc SDL2-devel make
```

#### On macOS:

- Install [Homebrew](https://brew.sh/) if you haven't already, then run:
  
```bash
brew update
brew install gcc sdl2 make
```

#### On Windows:

- Install [MinGW](http://www.mingw.org/) for GCC.
- Download SDL2 development libraries from [SDL's official website](https://www.libsdl.org/download-2.0.php) and set up the library in your MinGW environment.
- Use [Cygwin](https://www.cygwin.com/) or [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) for a Unix-like environment that includes `make`.

### Running the Game

After ensuring the prerequisites are installed, run the game with the following commands from the root of the project directory:

```bash
make
./GameOfLife
```

Note: On some systems, you may need to use `./GameOfLife.exe` instead of `./GameOfLife`.

## Rules of the Game

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states:

- Alive (`O`)
- Dead (`.`)

Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules:

1. **Birth**: A dead cell with exactly three live neighbors becomes a live cell.
2. **Survival**: A live cell with two or three live neighbors stays alive.
3. **Death by Overpopulation**: A live cell with more than three live neighbors dies.
4. **Death by Underpopulation**: A live cell with fewer than two live neighbors dies.

### Markdown Visualization of the Rules

#### Birth

```
Before          After
. . .           . O .
O O .    =>     O O .
. . .           . . .
```

#### Survival

```
Before          After
. O .           . O .
O O .    =>     O O .
. . .           . . .
```

#### Death by Overpopulation

```
Before          After
O O O           O . O
O O O    =>     O . O
. . .           . . .
```

#### Death by Underpopulation

```
Before          After
. . .           . . .
. O .    =>     . . .
. . .           . . .
```

## Contributing

Contributions to the Conway's Game of Life project are welcome! Please refer to the contributing guidelines for more information.
