# 2048 Project

A simple implementation of the game 2048 using C++. This version uses the
terminal as a display and keyboard input only.

The interface is implemented using the ncurses library to create a
terminal-based GUI to display the current board and score.

## Gameplay

You can use W/A/S/D or arrow keys to shift the tiles around. They will cascade
and tiles of the same value will combine together. The game begins with two "2"
tiles, and every move will spawn a new "2" tile in a randomly-chosen empty tile.
If two tiles combine, they turn into one tile with twice the value, and add that
to the score.

Try to get the highest score without running out of empty space to shift new
tiles around. The name of the game is 2048, which is a good target, but in this
version there is no "win" stage in the game. Just try to get the highest score
you possibly can!

For fairness, there is no undo, but if you really regret some of your moves you
can restart an entirely new game with the `r` key.

## Compilation

This program requires the [Meson build system][getting-meson]. To compile and run:

[getting-meson]: https://mesonbuild.com/Getting-meson.html

```console
$ meson setup build/
$ cd build/
$ meson compile
$ ./2048
```

## Code Structure

*There are comments throughout the code explaining specific parts, but here is a
general overview.*

The main gameplay logic is implemented in `game.cpp`. It holds the `Game` class,
which represents the current playthrough. It holds the current score, amount of
moves, and the tiles on the board. It provides methods to perform moves
(shifting the tiles) and some private methods for low level control over the
game (such as spawning new tiles).

The display/GUI logic is implemented in `display.cpp` using the `Display` class.
This uses a constructor to initialize the ncurses environment and a destructor
to terminate the ncurses window. The GUI gets updated through the `update()`
method which is called by `main()` after every move. 

The `main()` function handles input and passes it to the `Game` instance for
processing, then passes the `Game` to the `Display` to show the output.
