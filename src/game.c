#include "game.h"
#include <stdio.h>
#include <stdint.h>

static uint8_t pacman_row = 7;
static uint8_t pacman_column = 10;
static uint16_t score = 0;
#define BOARD_WIDTH 21
#define BOARD_HEIGHT 11

static const char board[BOARD_HEIGHT][BOARD_WIDTH] = {
    "#####################",
    "#........#..........#",
    "#.###.###.#.###.###.#",
    "#...................#",
    "#.###.#.#######.#.###",
    "#.....#.....#.....#.#",
    "#####.###.#.###.#####",
    "    #.....P.....#    ",
    "#####.#.#####.#.#####",
    "#.........#.........#",
    "#####################"
};

void game_run(void)
{
    const size_t row_count = sizeof(board) / sizeof(board[0]);

    puts("PAC-MAN C prototype");
    puts("-------------------");

    for (size_t row = 0; row < row_count; ++row) {
        puts(board[row]);
    }

    puts("\nNext step: add input and movement.");
}
