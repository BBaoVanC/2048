#include <iostream>

#include "display.hpp"
#include "game.hpp"

void test_display();

int main() {
    // test the display function
    //test_display();
    //return 0;

    Display display;

    bool continue_playing = true;
    while (continue_playing) {
        std::cout << "\nNEW GAME\n" << std::endl;
        Game game;
        // todo; change from true
        while (true) {
            display.update(game);
            std::cout << "Enter a move: ";
            char move;
            std::cin >> move;
            switch (move) {
                case 'h':
                    game.move(Move::Left);
                    break;
                case 'j':
                    game.move(Move::Down);
                    break;
                default:
                    std::cout << "Invalid move.";
                    break;
            }
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
