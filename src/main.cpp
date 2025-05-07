#include <iostream>

#include <ncurses.h>

#include "display.hpp"
#include "game.hpp"

void test_display();

int main() {
    // test the display function
    //test_display();
    //return 0;

    Display display;

    bool continue_playing_new_games = true;
    while (continue_playing_new_games) {
        Game game;
        // TODO: condition
        bool continue_playing = true;
        while (continue_playing) {
            display.update(game);

            int ch;
            ch = getch();
            switch (ch) {
                case 'a':
                case 'h':
                case KEY_LEFT:
                    game.move(Move::Left);
                    break;
                case 's':
                case 'j':
                case KEY_DOWN:
                    game.move(Move::Down);
                    break;
                case 'd':
                case 'l':
                case KEY_RIGHT:
                    game.move(Move::Right);
                    break;
                case 'w':
                case 'k':
                case KEY_UP:
                    game.move(Move::Up);
                    break;

                // quit
                case 'q':
                    continue_playing = false;
                    continue_playing_new_games = false;
                    break;
                // restart
                case 'r':
                    continue_playing = false;
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
