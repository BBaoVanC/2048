#include <algorithm> // max_element
#include <iostream>

#include "display.hpp"
#include "game.hpp"

void Display::update(Game &game) {
    std::cout << "Score: " << game.score << "\n"
        << "Moves: " << game.moves << "\n";

    std::cout << "\n";

    uint32_t max_width = log10(1 <<
    for (size_t y = 0; y < BOARD_SIZE; y++) {
        std::cout << "| ";
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            std::cout <<
        }
        std::cout << "\n";
    }
}
