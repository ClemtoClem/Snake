#include "tree.h"
#include "list.h"
#include "apple.h"
#include "timer.h"
#include <stdlib.h>

Tree *tree_create(Vec2 pos) {
    Tree *tree = calloc(1, sizeof(Tree));
    tree->position = pos;
    tree->age = 0;
    tree->state = TREE_YOUNG;
    tree->radius = 10;
    timer_init(&tree->timer, TREE_AGE_TIME, true);
    return tree;
}

void tree_update(Tree *tree, float dt, Game *game) {
    if (tree->state == TREE_DEAD) return;

    if (timer_update(&tree->timer, dt)) {
        tree->age++;
        if (tree->age > 25) {
            tree->state = TREE_DEAD;
            list_remove(&game->trees, tree);
            return;
        } else if (tree->age > 15) {
            tree->state = TREE_OLD;
            tree->radius = 35;
        } else if (tree->age > 5) {
            tree->state = TREE_NORMAL;
            tree->radius = 30;
        } else {
            tree->state = TREE_YOUNG;
            tree->radius = 20;
        }
    }
    
    // Apple spawning logic
    if (tree->state == TREE_NORMAL) {
        if (rand() % TREE_APPLE_SPAWN_CHANCE == 0) {
            Apple *apple = apple_create(tree->position);
            list_push_back(&game->apples, apple);
        }
    } else if (tree->state == TREE_OLD) {
        if (rand() % (TREE_APPLE_SPAWN_CHANCE * 2) == 0) { // Less chance when old
            Apple *apple = apple_create(tree->position);
            list_push_back(&game->apples, apple);
        }
    }
}

void tree_free(Tree *tree) {
    free(tree);
}