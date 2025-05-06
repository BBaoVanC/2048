#include "game.hpp"

Tile::Tile(): has_tile(false), exp(0) {}
Tile::Tile(uint32_t exp): has_tile(true), exp(exp) {}

Game::Game(): board(), score(0), moves(0) {
    // place the first two tiles
    this->spawn_tile();
    this->spawn_tile();
}
#include <iostream>
void Game::spawn_tile() { std::cout << "spawn tile" << std::endl; }
