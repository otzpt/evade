#ifndef TIMER_H
#define TIMER_H

typedef struct {
    long interval_ms;
    long last_ms;
} Timer;

void timer_init(Timer *t, long interval_ms);
int timer_due(Timer *t);

#endif
