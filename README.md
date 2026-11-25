# Evade

Simple TUI game made in C using ncurses made out of boredom one random morning.<br>
Decided to port this over to phantom (hackclub YSWS) so i can have more fun and more motivation to do this, why do i need motivation you might ask, well im not a game dev so for me this isn't that much fun to make but until now its being **fun**

## Features

Well, i dont know, its still in dev<br>

- **tick based timer**: well it has its own timer in a header file
- **super lightweight**: it is super lightweight, as it is literally a **'@'** dodging randomly generated **'#'** in a fixed y position descending the screen
- **death screen**: yea it is literally what you would expect from a death screen
- **maybe in the future**: points count, lives, reset button, better ascii, i cant do much im in internship.

## Notice

This one is small. The big ahh commit, i **think** the **2nd one**, has a commit message that was outsourced to an LLM (the commit message was outsourced not the code, the code is all mine), and it contains work done before the existence of this GH repo.

Big stuff, **Code might not even compile at current state, as some commits + push might come with uncompleted code, or bugs that i didnt have time to fix or check**

## Dependencies

**this is important if you want to try it out before i release binaries**

It needs **C23** because of bool types so it needs an extra tag or gcc 15.x and newer, and it needs **ncurses** too

## How to run

The game is not done **yet** so i dont see why you would be willing to run this.

```bash
git clone https://github.com/otzpt/evade && cd evade
```

then you compile it (**WARNING**: **needs gcc 14 or newer verify your version with gcc --version**)

```bash
gcc -Wall -Wextra main.c timer.c -O2 -o evade -lncurses -std=c23
```

and now finally you run it

```bash
./evade
```

**THIS TUTORIAL IS FOR LINUX AND YOU NEED GCC 14 OR NEWER INSTALLED AND C23 (SHOULD COME WITH GCC 14 AND NEWER)**
