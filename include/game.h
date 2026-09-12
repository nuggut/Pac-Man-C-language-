#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <stdint.h>

typedef enum {
	PACMAN_UP,
	PACMAN_DOWN,
	PACMAN_LEFT,
	PACMAN_RIGHT
} PacmanDirection;

void game_run(void);
uint8_t pacman_move(PacmanDirection direction);
void pacman_reset(void);
void pacman_get_position(uint8_t *row, uint8_t *column);

#endif
