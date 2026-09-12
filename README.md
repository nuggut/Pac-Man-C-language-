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

The current version is a console prototype that displays the initial board. Future steps will add input, movement, collision rules, pellets, ghosts, scoring, and a graphical interface.