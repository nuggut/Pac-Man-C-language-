#include "game.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

static uint8_t pacman_row = 23;
static uint8_t pacman_column = 13;

static const char board[BOARD_HEIGHT][BOARD_WIDTH + 1] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#o####.#####.##.#####.####o#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "######.##### ## #####.######",
    "######.##          ##.######",
    "######.## ###--### ##.######",
    "######.## #      # ##.######",
    "      .   #      #   .      ",
    "######.## #      # ##.######",
    "######.## ######## ##.######",
    "######.##          ##.######",
    "######.## ######## ##.######",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#o..##................##..o#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################"
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
            return PACMAN_NONE;
    }

    if (row < BOARD_HEIGHT && column < BOARD_WIDTH &&
        board[row][column] != '#' && board[row][column] != '-' &&
        board[row][column] != ' ') {
        pacman_row = row;
        pacman_column = column;
        return 1;
    }

    return 0;
}

PacmanDirection input_read_direction(void)
{
    int c;

    if (!_kbhit()) {
        return PACMAN_NONE;
    }

    c = _getch();

    if (c == 27 || c == 'q' || c == 'Q') {
        return PACMAN_EXIT;
    }

    if (c == 0 || c == 224) {
        c = _getch();
        switch (c) {
            case 72:
                return PACMAN_UP;
            case 80:
                return PACMAN_DOWN;
            case 75:
                return PACMAN_LEFT;
            case 77:
                return PACMAN_RIGHT;
            default:
                return PACMAN_NONE;
        }
    }

    switch (c) {
        case 'w':
        case 'W':
            return PACMAN_UP;
        case 's':
        case 'S':
            return PACMAN_DOWN;
        case 'a':
        case 'A':
            return PACMAN_LEFT;
        case 'd':
        case 'D':
            return PACMAN_RIGHT;
        default:
            return PACMAN_NONE;
    }
}


void pacman_reset(void)
{
    pacman_row = 23;
    pacman_column = 13;
}

void pacman_get_position(uint8_t *row, uint8_t *column)
{
    *row = pacman_row;
    *column = pacman_column;
}

void game_run(void)
{
    PacmanDirection current_direction = PACMAN_NONE;
    PacmanDirection requested_direction = PACMAN_NONE;
    PacmanDirection new_direction;

    pacman_reset();

    for (;;) {
        printf("\x1b[2J\x1b[H");
        puts("PAC-MAN C prototype");
        puts("WASD or arrow keys: move    Q or Esc: quit");

        for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
            for (uint8_t column = 0; column < BOARD_WIDTH; column++) {
                if (row == pacman_row && column == pacman_column) {
                    putchar('P');
                } else {
                    putchar(board[row][column]);
                }
            }
            putchar('\n');
        }

        new_direction = input_read_direction();
        if (new_direction == PACMAN_EXIT) {
            break;
        }
        if (new_direction != PACMAN_NONE) {
            requested_direction = new_direction;
        }

        if (requested_direction != PACMAN_NONE &&
            pacman_move(requested_direction)) {
            current_direction = requested_direction;
        } else {
            pacman_move(current_direction);
        }
        Sleep(150);
    }
}
