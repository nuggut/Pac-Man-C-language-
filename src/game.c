#include "game.h"

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

char game_get_tile(uint8_t row, uint8_t column)
{
    if (row >= BOARD_HEIGHT || column >= BOARD_WIDTH) {
        return ' ';
    }

    return board[row][column];
}

static uint8_t tile_is_walkable(uint8_t row, uint8_t column)
{
    char tile = board[row][column];

    return tile != '#' && tile != '-' &&
           (tile != ' ' || row == BOARD_TUNNEL_ROW);
}

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
            if (row == BOARD_TUNNEL_ROW && column == 0) {
                column = BOARD_WIDTH - 1;
            } else {
                column--;
            }
            break;
        case PACMAN_RIGHT:
            if (row == BOARD_TUNNEL_ROW && column == BOARD_WIDTH - 1) {
                column = 0;
            } else {
                column++;
            }
            break;
        default:
            return PACMAN_NONE;
    }

    if (row < BOARD_HEIGHT && column < BOARD_WIDTH &&
        tile_is_walkable(row, column)) {
        pacman_row = row;
        pacman_column = column;
        return 1;
    }

    return 0;
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
