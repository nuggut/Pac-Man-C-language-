#include "game.h"
#include <stdio.h>

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

uint8_t pacman_move(PacmanDirection direction)
{
    uint8_t row = pacman_row;
    uint8_t column = pacman_column;

    switch (direction) {
        case PACMAN_UP:
            row--;
            break;
        case PACMAN_DOWN:
            row++;
            break;
        case PACMAN_LEFT:
            column--;
            break;
        case PACMAN_RIGHT:
            column++;
            break;
        default:
            return 0;
    }

    if (row < BOARD_HEIGHT && column < BOARD_WIDTH && board[row][column] != '#') {
        pacman_row = row;
        pacman_column = column;
        return 1;
    }

    return 0;
}

void pacman_reset(void)
{
    pacman_row = 7;
    pacman_column = 10;
}

void pacman_get_position(uint8_t *row, uint8_t *column)
{
    *row = pacman_row;
    *column = pacman_column;
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
