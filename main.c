#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"

#define MAX_OBJECT 30
#define MAX_X 50
#define MAX_Y 20

/*
    NOTICE

    comment language may change or vary

    this may happen when im too concentrated so i just forget to type in eng
    hope this doesnt affect the reading experience for outsiders

    Have a good day!!
*/

void setup()
{
    curs_set(0);
    raw();
    noecho();
    keypad(stdscr, TRUE);
    //nodelay(); <- this makes cpu go vromm cause then loop runs at max speed
    timeout(25); // use ths instead of nodelay or 
}

void mov(int *y, int *x, int *pressed_key)
{
    if (*pressed_key == 'a' && *x > 2) {
        (*x)--;
    } else if (*pressed_key == 'd' && *x < MAX_X) {
        (*x)++;
    } else if (*pressed_key == 'w' && *y > 5) {
        (*y)--;
    } else if (*pressed_key == 's' && *y < MAX_Y) {
        (*y)++;
    }
}

void borders(void)
{
    for (int x = 1; x <= MAX_X + 1; x++) {
        mvaddch(4, x, '-');
        mvaddch(MAX_Y + 1, x, '-');
        mvaddch(MAX_Y + 3, x, '-');
    }
    for (int y = 4; y <= MAX_Y + 3; y++) {
        mvaddch(y, 1, '|');
        mvaddch(y, MAX_X + 1, '|');
    }
}

void hud(long *time_passed, long *last_passed, int *tries, float *points, float *multiplier)
{
    static int x = 1; // this is the starting x position were points are going to be written

    if (*time_passed != *last_passed) {
        *last_passed = *time_passed;
        if (*time_passed % 20 == 0) {
            *multiplier += 0.25;
            *points += (2.0 * *multiplier);
        } else { // using else here so its easier to read
            *points += (2.0 * *multiplier);
        }
    }
    
    mvprintw(MAX_Y + 2, x + 1, "Points: %.2f", *points);
    mvprintw(MAX_Y + 2, MAX_X - 10, "Tries: %d", *tries);
}

int colision(int *obs_x, int *obs_y, int *x, int *y)
{
    for (int i = 0; i < MAX_OBJECT; i++) {
        if (obs_x[i] == *x && obs_y[i] == *y) {
            return true;
        }
    }
    return false;
}

void obstacle(int *obs_x, int *obs_y, int *active, Timer *fall, Timer *spawn)
{
    int tick = timer_due(fall);

    if (timer_due(spawn) && *active < MAX_OBJECT) {
        obs_x[*active] = 2 + rand() % (MAX_X - 1);
        obs_y[*active] = 5;
        (*active)++;
    }

    for (int i = 0; i < *active; i++) {
        if (tick) {
            obs_y[i]++;
            if (obs_y[i] > MAX_Y) {
                obs_y[i] = 5;
                obs_x[i] = 2 + rand() % (MAX_X - 1);
            }
        }
        mvaddch(obs_y[i], obs_x[i], '#');
    }
}

int main(void) {
    srand(time(NULL));

    Timer fall, spawn;
    int active = 0;
    int obs_x[MAX_OBJECT], obs_y[MAX_OBJECT];

    timer_init(&fall, 200);
    timer_init(&spawn, 1000);

    for (int i = 0; i < MAX_OBJECT; i++) {
        obs_x[i] = 2 + rand() % 49;
        obs_y[i] = -1;
    }

    int x = 10;
    int y = 20;
    int tries = 1;
    float points = 0.0;
    float multiplier = 1.0;

    time_t start = time(NULL);
    long passed = 0;
    long last_passed = 0;

    initscr();
    setup();

    while(1) {
        bool dead = colision(obs_x, obs_y, &x, &y);
        int pressed_key = getch();        
        
        // time counting stuf
        passed = time(NULL) - start;

        if (pressed_key == 'q') {
            break;
        }
        
        if (!dead) {
            erase();
            borders();
            hud(&passed, &last_passed, &tries, &points, &multiplier);
            mov(&y, &x, &pressed_key);
            mvaddch(y, x, '@');
            obstacle(obs_x, obs_y, &active, &fall, &spawn);
            refresh();
        } else {
            erase();
            mvaddstr(MAX_Y/2, MAX_X/2, "you lost");
            mvaddstr((MAX_Y/2)+1, MAX_X/2, "press q to quit or r to restart");
            if (pressed_key == 'r') {
                x = 10;
                y = 20;

                active = 0;
                points = 0.0;
                multiplier = 1.0;
                tries++;

                // reset timers n shit
                timer_init(&fall, 200);
                timer_init(&spawn, 1000);
                start = time(NULL);
                last_passed = 0;

                for(int i = 0; i < MAX_OBJECT; i++) { 
                    obs_x[i] = 0; 
                    obs_y[i] = -1;  
                } 
                erase();
                continue;
            }
            refresh();
        }
    }    
    endwin();
    return 0;
}
