#ifndef TREE_H
#define TREE_H

#include "structs.h"

#define TREE_AGE_TIME           5000 // A tree ages every 5s
#define TREE_APPLE_SPAWN_CHANCE 200  // 1 in X chance to spawn an apple per update

Tree *tree_create(Vec2 pos);
void tree_update(Tree *tree, float dt, Game *game);
void tree_free(Tree *tree);

#endif // TREE_H