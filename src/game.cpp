#include <cassert>

#include <cstdlib> // random generation
#include <ctime> // time(NULL) for srand

#include <utility> // std::pair
#include <vector>

#include "game.hpp"

Tile::Tile(): has_tile(false), exp(0) {}
Tile::Tile(uint32_t exp): has_tile(true), exp(exp) {}
bool Tile::operator==(const Tile& other) {
    if (this->has_tile != other.has_tile) {
        return false;
    }

    if (this->has_tile) {
        return this->exp == other.exp;
    } else {
        // both this and other !has_tile (are empty)
        return true;
    }
}

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
        size_t x = rand() % BOARD_SIZE;
        size_t y = rand() % BOARD_SIZE;
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
        // this description based on the perspective of shifting left:
        // - start at the right, and see if there is an equal tile to the left
        // - if there is, then combine. otherwise, go left one tile and check again
        // - done if we reach the leftmost tile. should not run the check since there's nothing to the left of it
        // repeat this for each row
        case Move::Left:
            for (size_t y = 0; y < BOARD_SIZE; y++) {
                for (size_t x = 3; x > 0; x--) {
                    if (this->board[x][y].
                }
            }
            break;
    }
}
