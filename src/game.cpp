#include <cassert>

#include <cstdlib> // random generation
#include <ctime> // time(NULL) for srand

#include <utility> // std::pair
#include <vector>

#include "game.hpp"

Tile::Tile(): has_tile(false), exp(0) {}
Tile::Tile(uint32_t exp): has_tile(true), exp(exp) {}

void Game::spawn_tile() {
    // make sure there is an empty tile, otherwise we bail
    int empty_tiles = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (!this->board[x][y].has_tile) {
                empty_tiles++;
            }
        }
    }

    assert(empty_tiles > 0);

    while (true) {
        size_t x = rand() % 4;
        size_t y = rand() % 4;
        Tile *t = &this->board[x][y];
        if (!t->has_tile) {
            t->has_tile = true;
            t->exp = 1;
            break;
        }
    }
}

Game::Game(): board(), score(0), moves(0) {
    srand(time(NULL));

    // place the first two tiles
    this->spawn_tile();
    this->spawn_tile();
}

void Game::move(Move move) {
    switch (move) {
        case Move::Left:
            this->board[0][0].has_tile = true;
            this->board[0][0].exp = 16;
            break;
    }
}
