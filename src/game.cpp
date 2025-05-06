#include "game.hpp"

Game::Game(): board(), score(0), moves(0) {
    // place the first two tiles
    this.spawn_tile();
    this.spawn_tile();
}
