#ifndef PROJECT2_DISPLAY_HPP
#define PROJECT2_DISPLAY_HPP

#include "game.hpp"

class Display {
private:
    // remove the copy constructors thanks to rule of three
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;
public:
    Display();
    ~Display();
    // update the display based on current game state; will display output
    void update(Game& game);
};

#endif
