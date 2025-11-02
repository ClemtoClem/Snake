#ifndef TIMER_H
#define TIMER_H

#include "structs.h"

void timer_init(Timer *timer, float interval, bool loop);

// Return true if timer is finish
bool timer_update(Timer *timer, float dt);

void timer_restart(Timer *timer);

#endif /* TIMER_H */