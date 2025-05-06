#include <iostream>

#include "display.hpp"
#include "game.hpp"

void test_display();

int main() {
    // test the display function
    test_display();
    return 0;

    Display display;

    bool continue_playing = true;
    while (continue_playing) {
        Game game;
        // todo; change from true
        while (true) {
            std::cout << "Enter a move (: ";
        }
    }

    return 0;
}

void test_display() {
    Display display;
    Game game;
    game.board[2][1] = 7;
    game.board[1][1] = 2;
    game.board[3][3] = 12; // 4096
    display.update(game);
}
