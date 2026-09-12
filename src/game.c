#include "game.h"
#include <stdio.h>
#include <stdint.h>

static uint8_t pacman_row = 7;
static uint8_t pacman_column = 10;
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
    "    #...........#    ",
    "#####.#.#####.#.#####",
    "#.........#.........#",
    "#####################"
};

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
