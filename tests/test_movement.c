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
    pacman_reset();
    if (!expect_position(23, 13)) {
        return 1;
    }

    if (!pacman_move(PACMAN_LEFT) || !expect_position(23, 12)) {
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

    puts("movement tests passed");
    return 0;
}
