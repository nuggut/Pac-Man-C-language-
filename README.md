# Pac-Man in C

A Pac-Man game built step by step in C.

## Project layout

- `include/` - public headers
- `src/` - game source files
- `CMakeLists.txt` - portable build configuration

## Build and run with GCC on Windows

From the project root:

```powershell
cmake -S . -B build-mingw -G "MinGW Makefiles"
cmake --build build-mingw
.\build-mingw\pacman.exe
```

The current version is a playable console game with:

- WASD or arrow-key movement
- Pellet and power-pellet scoring
- Three lives and ghost collisions
- Ghost release, targeting, and tunnel wrapping
- A level-complete state when all pellets are collected

Press `q` or `Esc` to quit. The game logic is kept in `src/game.c`, separate from the Windows console renderer in `src/console.c`.