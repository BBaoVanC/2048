#include "game.hpp"

Tile::Tile(int exp): has_tile(true), exp(exp) {}

Game::Game(): board(), score(0), moves(0) {
    // place the first two tiles
    this->spawn_tile();
    this->spawn_tile();
}
Game::spawn_tile() { std::cout << "spawn tile" << std::endl; }
