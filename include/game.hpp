#ifndef PROJECT2_GAME_HPP
#define PROJECT2_GAME_HPP

#define BOARD_SIZE 4

#include <cstdint>

struct Tile {
    bool has_tile;
    // the exponent of the tile's value; the n in 2^n
    uint32_t exp;

    Tile();
    Tile(uint32_t exp);
    bool operator==(const Tile& other) const;
};

enum class Move {
    Left,
    Right,
    Up,
    Down,
};

enum class Status {
    
};

class Game {
private:
    // randomly place a "2" tile in an empty space
    void spawn_tile();

public:
    // shouldn't mutate these outside but making them public for easier access when reading
    Tile board[BOARD_SIZE][BOARD_SIZE];
    uint32_t score;
    uint32_t moves;

    Game();
    void move(Move move);
};

#endif
