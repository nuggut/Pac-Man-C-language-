cmake_minimum_required(VERSION 3.20)

project(pacman C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(pacman
    src/game.c
    src/main.c
)

target_include_directories(pacman PRIVATE include)

if(MSVC)
    target_compile_options(pacman PRIVATE /W4)
else()
    target_compile_options(pacman PRIVATE -Wall -Wextra -Wpedantic)
endif()
