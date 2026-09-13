#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <stdint.h>

#define BOARD_WIDTH 28
#define BOARD_HEIGHT 31

typedef enum {
	PACMAN_NONE = 0,
	PACMAN_UP,
	PACMAN_DOWN,
	PACMAN_LEFT,
	PACMAN_RIGHT,
	PACMAN_EXIT
} PacmanDirection;

void game_run(void);
uint8_t pacman_move(PacmanDirection direction);
PacmanDirection input_read_direction(void);
void pacman_reset(void);
void pacman_get_position(uint8_t *row, uint8_t *column);

#endif
