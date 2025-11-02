#ifndef SEED_H
#define SEED_H

#include "structs.h"

#define SEED_GERMINATE_TIME 10000 // 10 seconds to become a tree

Seed *seed_create(Vec2 pos);
void seed_update(Seed *seed, float dt, Game *game);
void seed_free(Seed *seed);

#endif // SEED_H