#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include "timer.h"

static long now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

void timer_init(timer *t, long interval_ms) 
{
    t->interval_ms = interval_ms;
    t->last_ms = now_ms();
}

int timer_due(Timer *t)
{
    long now = now_ms;

    if (now - t->last_ms >= t->interval_ms) {
        t->last_ms = now;
        return 1;
    }
    return 0;
}
