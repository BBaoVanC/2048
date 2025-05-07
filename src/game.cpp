#include <cassert>

#include <cstdlib> // random generation
#include <ctime> // time(NULL) for srand

#include <utility> // std::pair
#include <vector>

#include "game.hpp"

Tile::Tile(): has_tile(false), exp(0) {}
Tile::Tile(uint32_t exp): has_tile(true), exp(exp) {}
bool Tile::operator==(const Tile& other) const {
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
    // whether to add to the moves counter
    bool made_move = false;
    switch (move) {
        // this description based on the perspective of shifting left:
        //
        // first, merge any tiles that can be
        // - start at the right, and see if there is an equal tile to the left
        // - if there is, then delete add right to left, and delete right. otherwise, go left one tile and check again
        // - done if we reach the leftmost tile. should not run the check since there's nothing to the left of it
        //
        // then, shift everything to the edge
        //
        // repeat all of this for each row
        case Move::Left:
            for (size_t y = 0; y < BOARD_SIZE; y++) {
                for (size_t x = BOARD_SIZE - 1; x > 0; x--) {
                    Tile *left = &this->board[x - 1][y];
                    Tile *right = &this->board[x][y];
                    if (left->has_tile && *left == *right) {
                        left->exp++;
                        right->has_tile = false;
                        break;
                    }
                }
                ssize_t first_x = -1;
                if (!this->board[0][y].has_tile) {
                    // find the first tile
                    for (size_t x = 0; x < BOARD_SIZE; x++) {
                        if (this->board[x][y].has_tile) {
                            first_x = x;
                        }
                    }
                }
                if (first_x > 0) {
                    // we need to move everything left by first_x many tiles
                    // skip the rightmost tile because it can be cleared after the loop
                    for (size_t x = 0; x < BOARD_SIZE - 1; x++) {
                        this->board[x][y] = this->board[x + first_x][y];
                    }
                    // clear that last tile
                    this->board[BOARD_SIZE - 1][y].has_tile = false;
                }
            }

                        // FIXME debug
                        this->board[0][0].has_tile = true;
                        this->board[0][0].exp = 5;
            break;
    }
}
