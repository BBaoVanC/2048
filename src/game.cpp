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

// get tiles based on current x/y reference frame for the axes
static Tile *get_tile_at_orientation(Tile board[BOARD_SIZE][BOARD_SIZE], bool orientation, size_t j, size_t k) {
    if (orientation) {
        return &board[k][j];
    } else {
        return &board[j][k];
    }
}
// FIXME: remove this include
#include <iostream>
// this description based on the perspective of shifting left (orientation = false; direction = false):
//
// first, merge any tiles that can be
// - start at the right, and see if there is an equal tile to the left
// - if there is, then delete add right to left, and delete right. otherwise, go left one tile and check again
// - done if we reach the leftmost tile. should not run the check since there's nothing to the left of it
//
// then, shift everything to the edge
//
// repeat all of this for each row
//
// orientation: true = up/down; false = left/right
// direction: true = down/right; false = up/left
// RETURNS: -1 if a move was not made, otherwise the score to be added
static int64_t shift_tiles(Tile board[BOARD_SIZE][BOARD_SIZE], bool orientation, bool direction) {
    int64_t score_delta = -1;

    // j is the axis to be compressing along; k is the cross axis (vertical if shifting horizontally)

    // doesn't matter which direction we traverse the cross axis

    for (size_t k = 0; k < BOARD_SIZE; k++) {
        // too complex to write in a for loop definition
        size_t j;
        if (direction) {
            j = 0;
        } else {
            j = BOARD_SIZE - 1;
        }
        while ((direction && j < BOARD_SIZE - 1) || (!direction && j > 0)) {
            Tile *tile_current = get_tile_at_orientation(board, orientation, j, k);
            Tile *tile_into;
            if (direction) {
                tile_into = get_tile_at_orientation(board, orientation, j + 1, k);
            } else {
                tile_into = get_tile_at_orientation(board, orientation, j - 1, k);
            }
            if (!tile_current->has_tile) {
                // ignore it
            } else if (!tile_into->has_tile) {
                // move tile to empty space
                *tile_into = *tile_current;
                tile_current->has_tile = false;
                // a move was made
                if (score_delta == -1) { score_delta = 0; }
            } else if (tile_current->exp == tile_into->exp) {
                tile_into->exp++;
                tile_current->has_tile = false;
                // a move was made, and added score
                if (score_delta == -1) { score_delta = 0; }
                score_delta += 1 << tile_into->exp;
            }

            if (direction) {
                j++;
            } else {
                j--;
            }
        }
    }

    return score_delta;

    //
    for (size_t k = 0; k < BOARD_SIZE; k++) {
        // checking conditions will be too complex to write inside a for loop definition
        ssize_t j;
        if (direction) {
            j = 0;
        } else {
            j = BOARD_SIZE - 1;
        }
        while ((direction && j < BOARD_SIZE - 1) || (!direction && j > 0)) {
            // the tile to merge into
            Tile *tile_merge;
            if (direction) {
                tile_merge = get_tile_at_orientation(board, orientation, j + 1, k);
            } else {
                tile_merge = get_tile_at_orientation(board, orientation, j - 1, k);
            }
            // the tile to delete from the merge
            Tile *tile_delete = get_tile_at_orientation(board, orientation, j, k);
            if (tile_merge->has_tile && *tile_merge == *tile_delete) {
                board[0][0].has_tile = true;
                board[0][0].exp = 5;
                if (direction) {
                    tile_delete->exp++;
                    tile_merge->has_tile = false;
                } else {
                    tile_merge->exp++;
                    tile_delete->has_tile = false;
                }
                score_delta = 1 << tile_merge->exp;
                break;
            }

            if (direction) { j++; } else { j--; }
        }

        ssize_t first_j = -1;
        if ( (!direction && !get_tile_at_orientation(board, orientation, 0, k)->has_tile) ||
              (direction && !get_tile_at_orientation(board, orientation, BOARD_SIZE - 1, k)->has_tile) ) {
            // find the first tile
            ssize_t j;
            if (direction) {
                j = BOARD_SIZE - 1;
            } else {
                j = 0;
            }
            while ((direction && j >= 0) || (!direction && j < BOARD_SIZE)) {
                if (get_tile_at_orientation(board, orientation, j, k)->has_tile) {
                    first_j = j;
                }
                if (direction) { j--; } else { j++; }
            }
        }
        std::cerr << k << ' ' << first_j;
        std::cerr << "\n\n";
        continue;

        if (first_j > 0) {
            if (score_delta == -1) {
                // if we didn't combine anything but do need to shift over some stuff
                score_delta = 0;
            }

            // we need to move everything left by first_j many tiles
            // skip the rightmost tile because it can be cleared after the loop
            size_t j;
            if (direction) {
                j = BOARD_SIZE - 1;
            } else {
                j = 0;
            }
            while ((direction && j > 0) || (!direction && j < BOARD_SIZE - 1)) {
                if (direction) {
                    *get_tile_at_orientation(board, orientation, j, k) = *get_tile_at_orientation(board, orientation, j - first_j, k);
                } else {
                    *get_tile_at_orientation(board, orientation, j, k) = *get_tile_at_orientation(board, orientation, j + first_j, k);
                }
                if (direction) { j--; } else { j++; }
            }
            // clear that last tile
            if (direction) {
                get_tile_at_orientation(board, orientation, 0, k)->has_tile = false;
            } else {
                get_tile_at_orientation(board, orientation, BOARD_SIZE - 1, k)->has_tile = false;
            }
        }
    }

    return score_delta;
}
void Game::move(Move move) {
    // whether to add to the moves counter
    int64_t score_delta;
    switch (move) {
        case Move::Left:
            score_delta = shift_tiles(this->board, false, false);
            break;
        case Move::Right:
            score_delta = shift_tiles(this->board, false, true);
            break;
        case Move::Up:
            score_delta = shift_tiles(this->board, true, false);
            break;
        case Move::Down:
            score_delta = shift_tiles(this->board, true, true);
            break;
    }

    if (score_delta >= 0) {
        this->score += score_delta;
        this->spawn_tile();
        this->moves++;
    }
}
