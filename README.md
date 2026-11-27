# Evade

Simple TUI game made in C using ncurses made out of boredom one random morning.<br>
Decided to port this over to phantom (hackclub YSWS) so i can have more fun and more motivation to do this, why do i need motivation you might ask, well im not a game dev so for me this isn't that much fun to make but until now its being **fun**

## Features

- **tick based timer**: well it has its own timer in a header file
- **super lightweight**: it is super lightweight, as it is literally a **'@'** dodging randomly generated **'#'** descending the screen
- **death screen**: yea it is literally what you would expect from a death screen
- **points system with multiplier**: counts points add 0.25x to multiplier every 20sec, receive 2 points every second you survive
- **maybe in the future**: lives, reset button, better ascii, i cant do much im in internship.

## Notice

This one is small. The big ahh commit, i **think** the **2nd one**, has a commit message that was outsourced to an LLM (the commit message was outsourced not the code, the code is all mine), and it contains work done before the existence of this GH repo.

Big stuff, **Code might not compile, or game might have bugs at current state, as some commits + push might come with uncompleted code, or bugs that i didnt have time to fix or check**

## Dependencies

- **ncurses**: for TUI, i dont use raw ascii
- **LINUX**: for posix api, for now linux only, windows support planned

## How to run

The game is not done **yet** so i dont see why you would be willing to run this.

```bash
git clone https://github.com/otzpt/evade && cd evade
```

then you compile it (**WARNING**: **needs gcc 5 (works on gcc 4.x but needs -std=c99) or newer verify your version with gcc --version**)

```bash
gcc -Wall -Wextra main.c timer.c -O2 -o evade -lncurses
```

and now finally you run it

```bash
./evade
```

**THIS TUTORIAL IS LINUX ONLY AND YOU NEED GCC 4.x(bare minimum using -std=c99) OR NEWER INSTALLED AND C99+ (SHOULD DEFAULT WITH GCC 5 AND NEWER)**
