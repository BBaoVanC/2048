#include <iostream>

#include <ncurses.h>

#include "display.hpp"
#include "game.hpp"

int main() {
    Display display;

    bool continue_playing_new_games = true;
    while (continue_playing_new_games) {
        Game game;

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
