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

Game::Game(): board(), score(0), moves(0), status(Status::Playing) {
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
    // TODO: add game over screen (not currently working)
    } else if (false) {
        // if there's no possible moves, the game is over
        for (ssize_t y = 0; y < BOARD_SIZE; y++) {
            for (ssize_t x = 0; x < BOARD_SIZE; x++) {
                // possible moves can be either up/down or left/right
                Tile *current = &this->board[x][y];
                for (ssize_t diff = -1; diff <= 1; diff += 2) {
                    if (x + diff < 0 || y + diff < 0 || x + diff >= BOARD_SIZE || y + diff >= BOARD_SIZE) {
                        // ignore out of bounds tiles
                        continue;
                    }

                    if (!this->board[x + diff][y].has_tile || !this->board[x][y + diff].has_tile) {
                        // there's an empty tile available
                        return;
                    }
                    if (this->board[x + diff][y] == *current || this->board[x][y + diff] == *current) {
                        // there's a tile that can be combined
                        return;
                    }
                }
            }
        }
    }

    //// otherwise, no possible moves, the game is over.
    //this->status = Status::Ended;
}
