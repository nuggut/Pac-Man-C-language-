#include "game.h"
#include <stdio.h>

static int expect_position(uint8_t expected_row, uint8_t expected_column)
{
    uint8_t row;
    uint8_t column;

    pacman_get_position(&row, &column);
    if (row != expected_row || column != expected_column) {
        printf("expected position (%u, %u), got (%u, %u)\n",
               expected_row, expected_column, row, column);
        return 0;
    }

    return 1;
}

int main(void)
{
    pacman_start_game();
    if (pacman_get_score() != 10 ||
        pacman_get_lives() != PACMAN_STARTING_LIVES ||
        pacman_get_pellets_remaining() == 0 ||
        pacman_level_complete()) {
        return 1;
    }

    pacman_reset();
    if (!expect_position(23, 13)) {
        return 1;
    }

    if (!pacman_move(PACMAN_LEFT) || !expect_position(23, 12)) {
        return 1;
    }
    if (pacman_get_score() != 20 || game_get_tile(23, 12) != ' ') {
        return 1;
    }

    pacman_lose_life();
    if (pacman_get_lives() != PACMAN_STARTING_LIVES - 1 ||
        !expect_position(23, 13)) {
        return 1;
    }

    uint8_t ghost_row;
    uint8_t ghost_column;
    ghost_get_position(0, &ghost_row, &ghost_column);
    if (ghost_row != 14 || ghost_column != 13 ||
        ghosts_collide_with_pacman()) {
        return 1;
    }
    ghosts_update();
    ghost_get_position(0, &ghost_row, &ghost_column);
    if (ghost_row >= BOARD_HEIGHT || ghost_column >= BOARD_WIDTH ||
        game_get_tile(ghost_row, ghost_column) == '#') {
        return 1;
    }

    ghosts_reset();
    for (int update = 0; update < 6; update++) {
        ghosts_update();
    }
    if (ghost_is_released(0)) {
        return 1;
    }
    ghosts_update();
    ghost_get_position(0, &ghost_row, &ghost_column);
    if (!ghost_is_released(0) || ghost_row != 8 || ghost_column != 12) {
        return 1;
    }

    pacman_reset();
    if (pacman_move(PACMAN_UP) || !expect_position(23, 13)) {
        return 1;
    }

    pacman_reset();
    if (pacman_move(PACMAN_DOWN) || !expect_position(23, 13)) {
        return 1;
    }

    pacman_reset();
    if (pacman_move(PACMAN_NONE) || !expect_position(23, 13)) {
        return 1;
    }

    pacman_reset();
    for (int move = 0; move < 7; move++) {
        if (!pacman_move(PACMAN_LEFT)) {
            return 1;
        }
    }
    for (int move = 0; move < 9; move++) {
        if (!pacman_move(PACMAN_UP)) {
            return 1;
        }
    }
    for (int move = 0; move < 6; move++) {
        if (!pacman_move(PACMAN_LEFT)) {
            return 1;
        }
    }
    if (!expect_position(14, 0) ||
        !pacman_move(PACMAN_LEFT) || !expect_position(14, 27) ||
        !pacman_move(PACMAN_RIGHT) || !expect_position(14, 0)) {
        return 1;
    }

    puts("movement tests passed");
    return 0;
}
