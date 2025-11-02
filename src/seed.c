#include "seed.h"
#include "tree.h"
#include "timer.h"
#include "list.h"
#include <stdlib.h>

Seed *seed_create(Vec2 pos) {
    Seed *seed = calloc(1, sizeof(Seed));
    seed->position = pos;
    timer_init(&seed->timer, SEED_GERMINATE_TIME, false);
    return seed;
}

void seed_update(Seed *seed, float dt, Game *game) {
    if (timer_update(&seed->timer, dt)) {
        Tree *tree = tree_create(seed->position);
        list_push_back(&game->trees, tree);
        list_remove(&game->seeds, seed); // This will free the seed's node
    }
}

void seed_free(Seed *seed) {
    free(seed);
}