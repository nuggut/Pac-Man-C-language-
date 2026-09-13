cmake_minimum_required(VERSION 3.20)

project(pacman C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

enable_testing()

add_executable(pacman
    src/game.c
    src/main.c
)

target_include_directories(pacman PRIVATE include)

add_executable(pacman_movement_test
    src/game.c
    tests/test_movement.c
)

target_include_directories(pacman_movement_test PRIVATE include)
add_test(NAME pacman_movement_test COMMAND pacman_movement_test)

if(MSVC)
    target_compile_options(pacman PRIVATE /W4)
    target_compile_options(pacman_movement_test PRIVATE /W4)
else()
    target_compile_options(pacman PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(pacman_movement_test PRIVATE -Wall -Wextra -Wpedantic)
endif()
