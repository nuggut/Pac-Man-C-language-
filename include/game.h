#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <stdint.h>

#define BOARD_WIDTH 28
#define BOARD_HEIGHT 31
#define BOARD_TUNNEL_ROW 14
#define PACMAN_STARTING_LIVES 3
#define GHOST_COUNT 4

typedef enum {
	PACMAN_NONE = 0,
	PACMAN_UP,
	PACMAN_DOWN,
	PACMAN_LEFT,
	PACMAN_RIGHT,
	PACMAN_EXIT
} PacmanDirection;

uint8_t pacman_move(PacmanDirection direction);
void pacman_start_game(void);
void pacman_reset(void);
void pacman_lose_life(void);
void pacman_get_position(uint8_t *row, uint8_t *column);
uint32_t pacman_get_score(void);
uint8_t pacman_get_lives(void);
uint16_t pacman_get_pellets_remaining(void);
uint8_t pacman_level_complete(void);
char game_get_tile(uint8_t row, uint8_t column);
void ghosts_reset(void);
void ghosts_update(void);
void ghost_get_position(uint8_t ghost, uint8_t *row, uint8_t *column);
uint8_t ghost_is_released(uint8_t ghost);
uint8_t ghosts_collide_with_pacman(void);

#endif
