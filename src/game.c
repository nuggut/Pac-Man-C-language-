#include "game.h"
#include <stdio.h>
#include <stdint.h>

static uint8_t pacman_row = 7;
static uint8_t pacman_column = 10;
#define BOARD_WIDTH 21
#define BOARD_HEIGHT 11
#define BOARD_SIZE (BOARD_WIDTH * BOARD_HEIGHT)
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

static const char board[BOARD_HEIGHT][BOARD_WIDTH] = {
    "#####################",
    "#........#..........#",
    "#.###.###.#.###.###.#",
    "#...................#",
    "#.###.#.#######.#.###",
    "#.....#.....#.....#.#",
    "#####.###.#.###.#####",
    "    #...........#    ",
    "#####.#.#####.#.#####",
    "#.........#.........#",
    "#####################"
};

void pacman_move(uint8_t direction)
{
    uint8_t row = pacman_row;
    uint8_t column = pacman_column;

    switch (direction) {
        case UP: // up
            row--;
            break;
        case DOWN: // down
            row++;
            break;
        case LEFT: // left
            column--;
            break;
        case RIGHT: // right
            column++;
            break;
    }

    if (row < BOARD_HEIGHT && column < BOARD_WIDTH && board[row][column] != '#') {
        pacman_row = row;
        pacman_column = column;
    }
    return;
}

void game_run(void)
{
    puts("PAC-MAN C prototype");
    puts("-------------------");
    for (unsigned char row = 0; row < BOARD_HEIGHT; row++) {
        for (unsigned char column = 0; column < BOARD_WIDTH; column++) {
            if (row == pacman_row && column == pacman_column) {
                putchar('P');
            } else {
                putchar(board[row][column]);
            }
        }
        putchar('\n');
    }

    puts("\nNext step: add input and movement.");
}
