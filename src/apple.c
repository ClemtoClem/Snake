#include "apple.h"
#include "timer.h"
#include "seed.h"
#include "list.h"
#include <stdlib.h>

Apple *apple_create(Vec2 pos) {
    Apple *apple = calloc(1, sizeof(Apple));
    apple->position = pos;
    apple->state = APPLE_FLOWER;
    timer_init(&(apple->timer), APPLE_GERMINATE_TIME, false);
    return apple;
}

void apple_update(Apple *apple, float dt, Game *game) {
    if (apple->state == APPLE_FLOWER) {
        if (timer_update(&(apple->timer), dt)) {
            apple->state = APPLE_RIPE;
            timer_init(&(apple->timer), APPLE_FELL_TIME, false);
        }
    } else if (apple->state == APPLE_RIPE) {
        if (timer_update(&(apple->timer), dt)) {
            apple->state = APPLE_FELL;
            timer_init(&(apple->timer), APPLE_ROTTING_TIME, false);
        }
    } else if (apple->state == APPLE_FELL) {
        if (timer_update(&(apple->timer), dt)) {
            apple->state = APPLE_ROTTED;
            timer_init(&(apple->timer), APPLE_DECOMPOSITION_TIME, false);
        }
    } else if (apple->state == APPLE_ROTTED) {
        if (timer_update(&(apple->timer), dt)) {
            apple->state = APPLE_DECOMPOSED;
        }
    } else if (apple->state == APPLE_INGESTED) {
        if (timer_update(&(apple->timer), dt)) {
            apple->state = APPLE_DIGESTED;
        }
    } else if (apple->state == APPLE_DECOMPOSED || apple->state == APPLE_DIGESTED) {
        Seed *seed = seed_create(apple->position);
        list_push_front(&(game->seeds), seed);
        list_remove(&(game->apples), apple);
    }
}

void apple_ingested(Apple *apple) {
    apple->state = APPLE_INGESTED;
    timer_init(&(apple->timer), APPLE_DIGESTION_TIME, false);
}

void apple_free(Apple *apple) {
    free(apple);
}
