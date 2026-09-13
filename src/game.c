#include "game.h"

static uint8_t pacman_row = 23;
static uint8_t pacman_column = 13;
static uint8_t pellets[BOARD_HEIGHT][BOARD_WIDTH];
static uint16_t pellets_remaining;
static uint32_t pacman_score;
static uint8_t pacman_lives;
static uint8_t game_initialized;

typedef struct {
    uint8_t row;
    uint8_t column;
    PacmanDirection direction;
    uint8_t released;
} GhostState;

static GhostState ghosts[GHOST_COUNT];

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

static const GhostState ghost_start_positions[GHOST_COUNT] = {
    {14, 13, PACMAN_LEFT, 0},
    {14, 14, PACMAN_RIGHT, 0},
    {14, 12, PACMAN_LEFT, 0},
    {14, 15, PACMAN_RIGHT, 0}
};

#define GHOST_EXIT_ROW 8
#define GHOST_EXIT_COLUMN 12

static void collect_pellet(uint8_t row, uint8_t column)
{
    if (pellets[row][column] == 1) {
        pacman_score += 10;
        pellets[row][column] = 0;
        pellets_remaining--;
    } else if (pellets[row][column] == 2) {
        pacman_score += 50;
        pellets[row][column] = 0;
        pellets_remaining--;
    }
}

static void ensure_game_initialized(void)
{
    if (!game_initialized) {
        pacman_start_game();
    }
}

char game_get_tile(uint8_t row, uint8_t column)
{
    ensure_game_initialized();

    if (row >= BOARD_HEIGHT || column >= BOARD_WIDTH) {
        return ' ';
    }

    if ((board[row][column] == '.' || board[row][column] == 'o') &&
        pellets[row][column] == 0) {
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

static uint8_t next_position(uint8_t current_row, uint8_t current_column,
                             PacmanDirection direction, uint8_t *next_row,
                             uint8_t *next_column, uint8_t ghost_in_house)
{
    *next_row = current_row;
    *next_column = current_column;

    switch (direction) {
        case PACMAN_UP:
            (*next_row)--;
            break;
        case PACMAN_DOWN:
            (*next_row)++;
            break;
        case PACMAN_LEFT:
            if (current_row == BOARD_TUNNEL_ROW && current_column == 0) {
                *next_column = BOARD_WIDTH - 1;
            } else {
                (*next_column)--;
            }
            break;
        case PACMAN_RIGHT:
            if (current_row == BOARD_TUNNEL_ROW &&
                current_column == BOARD_WIDTH - 1) {
                *next_column = 0;
            } else {
                (*next_column)++;
            }
            break;
        default:
            return 0;
    }

    if (*next_row >= BOARD_HEIGHT || *next_column >= BOARD_WIDTH) {
        return 0;
    }

    if (ghost_in_house) {
        return board[*next_row][*next_column] != '#';
    }

    return tile_is_walkable(*next_row, *next_column);
}

uint8_t pacman_move(PacmanDirection direction)
{
    uint8_t row = pacman_row;
    uint8_t column = pacman_column;
    uint8_t next_row;
    uint8_t next_column;

    ensure_game_initialized();

    if (next_position(row, column, direction, &next_row, &next_column, 0)) {
        pacman_row = next_row;
        pacman_column = next_column;
        collect_pellet(next_row, next_column);
        return 1;
    }

    return 0;
}

void pacman_start_game(void)
{
    pellets_remaining = 0;
    pacman_score = 0;
    pacman_lives = PACMAN_STARTING_LIVES;

    for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
        for (uint8_t column = 0; column < BOARD_WIDTH; column++) {
            if (board[row][column] == '.') {
                pellets[row][column] = 1;
                pellets_remaining++;
            } else if (board[row][column] == 'o') {
                pellets[row][column] = 2;
                pellets_remaining++;
            } else {
                pellets[row][column] = 0;
            }
        }
    }

    game_initialized = 1;
    pacman_reset();
    collect_pellet(pacman_row, pacman_column);
    ghosts_reset();
}

void pacman_reset(void)
{
    pacman_row = 23;
    pacman_column = 13;
}

void pacman_lose_life(void)
{
    ensure_game_initialized();

    if (pacman_lives > 0) {
        pacman_lives--;
    }

    pacman_reset();
}

void pacman_get_position(uint8_t *row, uint8_t *column)
{
    *row = pacman_row;
    *column = pacman_column;
}

void ghosts_reset(void)
{
    for (uint8_t ghost = 0; ghost < GHOST_COUNT; ghost++) {
        ghosts[ghost] = ghost_start_positions[ghost];
    }
}

void ghosts_update(void)
{
    static const PacmanDirection directions[] = {
        PACMAN_UP, PACMAN_LEFT, PACMAN_DOWN, PACMAN_RIGHT
    };

    ensure_game_initialized();

    for (uint8_t ghost = 0; ghost < GHOST_COUNT; ghost++) {
        uint8_t best_row = ghosts[ghost].row;
        uint8_t best_column = ghosts[ghost].column;
        uint16_t best_distance = UINT16_MAX;
        PacmanDirection best_direction = ghosts[ghost].direction;
        uint8_t target_row = ghosts[ghost].released
                             ? pacman_row : GHOST_EXIT_ROW;
        uint8_t target_column = ghosts[ghost].released
                                ? pacman_column : GHOST_EXIT_COLUMN;

        for (uint8_t direction_index = 0;
             direction_index < sizeof(directions) / sizeof(directions[0]);
             direction_index++) {
            uint8_t next_row;
            uint8_t next_column;
            uint16_t distance;

            if (!next_position(ghosts[ghost].row, ghosts[ghost].column,
                               directions[direction_index], &next_row,
                               &next_column, !ghosts[ghost].released)) {
                continue;
            }

            distance = (uint16_t)(next_row > target_row
                                  ? next_row - target_row
                                  : target_row - next_row) +
                       (uint16_t)(next_column > target_column
                                  ? next_column - target_column
                                  : target_column - next_column);
            if (distance < best_distance) {
                best_distance = distance;
                best_row = next_row;
                best_column = next_column;
                best_direction = directions[direction_index];
            }
        }

        ghosts[ghost].row = best_row;
        ghosts[ghost].column = best_column;
        ghosts[ghost].direction = best_direction;
        if (!ghosts[ghost].released &&
            best_row == GHOST_EXIT_ROW &&
            best_column == GHOST_EXIT_COLUMN) {
            ghosts[ghost].released = 1;
        }
    }
}

void ghost_get_position(uint8_t ghost, uint8_t *row, uint8_t *column)
{
    ensure_game_initialized();

    if (ghost >= GHOST_COUNT) {
        *row = 0;
        *column = 0;
        return;
    }

    *row = ghosts[ghost].row;
    *column = ghosts[ghost].column;
}

uint8_t ghost_is_released(uint8_t ghost)
{
    ensure_game_initialized();

    if (ghost >= GHOST_COUNT) {
        return 0;
    }

    return ghosts[ghost].released;
}

uint8_t ghosts_collide_with_pacman(void)
{
    ensure_game_initialized();

    for (uint8_t ghost = 0; ghost < GHOST_COUNT; ghost++) {
        if (ghosts[ghost].row == pacman_row &&
            ghosts[ghost].column == pacman_column) {
            return 1;
        }
    }

    return 0;
}

uint32_t pacman_get_score(void)
{
    ensure_game_initialized();
    return pacman_score;
}

uint8_t pacman_get_lives(void)
{
    ensure_game_initialized();
    return pacman_lives;
}

uint16_t pacman_get_pellets_remaining(void)
{
    ensure_game_initialized();
    return pellets_remaining;
}

uint8_t pacman_level_complete(void)
{
    ensure_game_initialized();
    return pellets_remaining == 0;
}
