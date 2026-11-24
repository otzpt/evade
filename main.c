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
    if (*pressed_key == 'a' && *x >= 2) {
        (*x)--;
    } else if (*pressed_key == 'd' && *x < MAX_X) {
        (*x)++;
    } else if (*pressed_key == 'w' && *y >= 5) {
        (*y)--;
    } else if (*pressed_key == 's' && *y < MAX_Y) {
        (*y)++;
    }
}

void obstacle(int *obs_x, int *obs_y, Timer *fall)
{
    int tick = timer_due(fall);
    static int counter = 0;

    if (counter < MAX_OBJECT) {
        for (int i = 0; i < MAX_OBJECT; i++) {
            // só corre quando o timer manda (tick), assim o input não bloqueia como com usleep
        // e o desenho não vai à velocidade máxima do loop
        if (tick) {
            obs_y[i]++;
            if (obs_y[i] > MAX_Y) {
                obs_y[i] = 5;
                obs_x[i] = 2 + rand() % (MAX_X - 1); // gerar posiçao aleatoria de x dentro dos limites
            }
        }
        mvaddch(obs_y[i], obs_x[i], '#');
    }
}

int main(void) {
    srand(time(NULL));

    Timer fall;
    int obs_x[MAX_OBJECT], obs_y[MAX_OBJECT];

    timer_init(&fall, 200);
    for (int i = 0; i < MAX_OBJECT; i++) {
        obs_x[i] = 2 + rand() % 49;
        obs_y[i] = 5 + rand() % 16;
    }

    int x = 10;
    int y = 20;

    initscr();
    setup();

    while(1) {
        int pressed_key = getch();        

        if (pressed_key == 'q') {
            break;
        }
        erase();
        mov(&y, &x, &pressed_key);
        mvaddch(y, x, '@');
        obstacle(obs_x, obs_y, &fall);
        refresh();
    }    
    endwin();
    return 0;
}
