#ifndef SNAKE_H
#define SNAKE_H

#include "structs.h"

void snake_init(Snake *snake);
void snake_update(Snake *snake, float dt);
void snake_grow(Snake *snake);
void snake_free(Snake *snake);
void snake_reset(Snake *snake);

#endif // SNAKE_H