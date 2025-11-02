#include "timer.h"

void timer_init(Timer *timer, float interval, bool loop) {
    if (!timer) return;
    timer->current = 0;
    timer->interval = interval;
    timer->loop = loop;
}

bool timer_update(Timer *timer, float dt) {
    if (!timer) return false;
    timer->current += dt;
    if (timer->current >= timer->interval) {
        if (timer->loop) timer->current = 0;
        return true;
    }
    return false;
}

void timer_restart(Timer *timer) {
    if (!timer)
    timer->current = 0;
}
