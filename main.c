#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"

#define MAX_OBJECT 30
#define MAX_X 50
#define MAX_Y 20

void setup()
{
    curs_set(0);
    raw();
    noecho();
    keypad(stdscr, TRUE);
}

void mov(int *y, int *x, int *pressed_key)
{
    if (*pressed_key == 'a' && *x >= 2) {
        (*x)--;
    } else if (*pressed_key == 'd' && *x <= MAX_X) {
        (*x)++;
    } else if (*pressed_key == 'w' && *y >= 5) {
        (*y)--;
    } else if (*pressed_key == 's' && *y <= MAX_Y) {
        (*y)++;
    }
}

void obstacle(int *player_x, int *player_y) // idk if this should check for position and colision or just that
{
    Timer fall;
    timer_init(&fall, 200);
    int obs_x = 2 + rand() % 49; // generate a random x pos

    for (int i = 0; i <= MAX_OBJECT; i++) { 
        mvaddch(MAX_Y - 1, *obs_x, '#');    
    }
}

int main(void) {
    int x = 10;
    int y = 20;

    srand(time(NULL)); // seed the random number

    initscr();
    setup();

    while(1) {
        for(int i = 0; i <= 1; i++) { mvaddch(y, x, '@'); }
        int pressed_key = getch();        

        if (pressed_key == 'q') {
            break;
        }
        erase();
        mov(&y, &x, &pressed_key);
        mvaddch(y, x, '@');
        refresh();
    }    
    endwin();
    return 0;
}
