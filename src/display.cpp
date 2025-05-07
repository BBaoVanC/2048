#include <cmath> // log10
#include <iostream>
#include <string>

#include <ncurses.h>

#include "display.hpp"
#include "game.hpp"

Display::Display() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

Display::~Display() {
    endwin();
}

static void print_horizontal_row_separator() {
    // 4 cols, each 7 chars wide, plus 5 separator bars
    std::cout << std::string(BOARD_SIZE * 7 + 5, '-') << "\n";
}
static void print_empty_row() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << '|' << std::string(7, ' ');
    }
    std::cout << '|' << std::endl;
}
void Display::update(Game& game) {
    std::cout << "Score: " << game.score << "\n"
        << "Moves: " << game.moves << "\n";

    std::cout << "\n";

    for (size_t y = 0; y < BOARD_SIZE; y++) {
        print_horizontal_row_separator();
        print_empty_row();
        std::cout << "|";
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            std::string tile_text;
            if (!game.board[x][y].has_tile) {
                tile_text = "";
            } else {
                tile_text = std::to_string(1 << game.board[x][y].exp);
            }

            //std::cout << std::vformat(tile_format, std::make_wformat_args(tile_text)) << " |";
            std::cout << std::format("{:^7}|", tile_text);
        }
        std::cout << "\n";
        print_empty_row();
    }
    print_horizontal_row_separator();

    std::cout << std::flush;
}
