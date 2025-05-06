#include <cmath> // log10
#include <iostream>
#include <string>

#include "display.hpp"
#include "game.hpp"

Display::Display() {
    std::cout << "Welcome to 2048!\n" << std::endl;
}

Display::~Display() {
    std::cout << "\n\n" << "GAME OVER" << std::endl;
}

void Display::update(Game &game) {
    std::cout << "Score: " << game.score << "\n"
        << "Moves: " << game.moves << "\n";

    std::cout << "\n";

    uint32_t largest_tile = 0;
    for (auto t : game.board) {
        if (t->has_tile && t->exp > largest_tile) {
            largest_tile = t->exp;
        }
    }

    // FIXME: future improvement: calculate the width of tiles based on largest tile currently on the board
    //
    // // the amount of chars in n is equal to log_10
    // uint32_t max_width = log10(1 << largest_tile);
    // std::string tile_format = "{:" + std::to_string(max_width) + "}";

    for (size_t y = 0; y < BOARD_SIZE; y++) {
        std::cout << "| ";
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            std::string tile_text;
            if (!game.board[x][y].has_tile) {
                tile_text = "";
            } else {
                tile_text = std::to_string(1 << game.board[x][y].exp);
            }

            //std::cout << std::vformat(tile_format, std::make_wformat_args(tile_text)) << " |";
            std::cout << std::format("{:7} |", tile_text);
        }
        std::cout << "\n";
    }

    std::cout << std::flush;
}
