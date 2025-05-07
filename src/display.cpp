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
    std::string p = std::string(BOARD_SIZE * 7 + 5, '-');
    printw("%s", p.c_str());
}
static void print_empty_row() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::string p = "|" + std::string(7, ' ');
        printw(p.c_str());
    }
    printw("|");
}
void Display::update(Game& game) {
    erase();

    mvprintw(0, 0, "Score: %u", game.score);
    mvprintw(1, 0, "Moves: %u", game.moves);

    size_t cur_y = 3;
    move(cur_y, 0);

    for (size_t y = 0; y < BOARD_SIZE; y++) {
        cur_y++;
        move(cur_y, 0);
        print_horizontal_row_separator();

        cur_y++;
        move(cur_y, 0);
        print_empty_row();

        cur_y++;
        move(cur_y, 0);
        printw("|");
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            std::string tile_text;
            if (!game.board[x][y].has_tile) {
                tile_text = "";
            } else {
                tile_text = std::to_string(1 << game.board[x][y].exp);
            }

            //std::cout << std::vformat(tile_format, std::make_wformat_args(tile_text)) << " |";
            std::string p = std::format("{:^7}|", tile_text);
            printw("%s", p.c_str());
        }

        cur_y++;
        move(cur_y, 0);
        print_empty_row();
    }

    cur_y++;
    move(cur_y, 0);
    print_horizontal_row_separator();

    refresh();
}
