#include "console.h"
#include "game.h"
#include <conio.h>
#include <inttypes.h>
#include <stdio.h>
#include <windows.h>

static PacmanDirection input_read_direction(void)
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

static int ghost_at_position(uint8_t row, uint8_t column)
{
    for (uint8_t ghost = 0; ghost < GHOST_COUNT; ghost++) {
        uint8_t ghost_row;
        uint8_t ghost_column;

        ghost_get_position(ghost, &ghost_row, &ghost_column);
        if (ghost_row == row && ghost_column == column) {
            return 1;
        }
    }

    return 0;
}

void game_run(void)
{
    PacmanDirection current_direction = PACMAN_NONE;
    PacmanDirection requested_direction = PACMAN_NONE;
    PacmanDirection new_direction;
    uint8_t pacman_row;
    uint8_t pacman_column;

    pacman_start_game();

    for (;;) {
        printf("\x1b[2J\x1b[H");
        printf("Score: %" PRIu32 "  Lives: %u  Pellets: %u\n",
               pacman_get_score(), pacman_get_lives(),
               pacman_get_pellets_remaining());
        if (pacman_level_complete()) {
            puts("LEVEL COMPLETE!");
        } else if (pacman_get_lives() == 0) {
            puts("GAME OVER!");
        }
        pacman_get_position(&pacman_row, &pacman_column);

        for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
            for (uint8_t column = 0; column < BOARD_WIDTH; column++) {
                if (row == pacman_row && column == pacman_column) {
                    putchar('P');
                } else if (ghost_at_position(row, column)) {
                    putchar('G');
                } else {
                    putchar(game_get_tile(row, column));
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

        if (!pacman_level_complete() && pacman_get_lives() > 0) {
            if (requested_direction != PACMAN_NONE &&
                pacman_move(requested_direction)) {
                current_direction = requested_direction;
            } else {
                pacman_move(current_direction);
            }

            ghosts_update();
            if (ghosts_collide_with_pacman()) {
                pacman_lose_life();
                ghosts_reset();
                current_direction = PACMAN_NONE;
                requested_direction = PACMAN_NONE;
            }
        }
        Sleep(150);
    }
}
