#include "game.h"
#include "snake.h"
#include "tree.h"
#include "apple.h"
#include "seed.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void game_init(Game *game, SDL_Renderer *renderer) {
    // Initialiser le tileset
    if (!tileset_init(&game->tileset, renderer, "tileset.png")) {
        // Gérer l'erreur si l'image n'est pas trouvée
        exit(1);
    }
    
    snake_init(&game->snake);
    list_init(&game->trees);
    list_init(&game->apples);
    list_init(&game->seeds);

    for (int i = 0; i < 40 + rand() % 50; ++i) {
        Vec2 pos = {(float)(rand() % (WORLD_SIZE_W / TILE_SIZE) * TILE_SIZE), 
                    (float)(rand() % (WORLD_SIZE_H / TILE_SIZE) * TILE_SIZE)};
        Tree *t = tree_create(pos);
        list_push_back(&game->trees, t);
    }
}

void game_input(Game *g, SDL_Event *e) {
    if (e->type == SDL_EVENT_KEY_DOWN) {
        switch (e->key.key) {
            case SDLK_UP: 
                if (g->snake.direction != DIR_DOWN) g->snake.direction = DIR_UP; 
                break;
            case SDLK_DOWN: 
                if (g->snake.direction != DIR_UP) g->snake.direction = DIR_DOWN; 
                break;
            case SDLK_LEFT: 
                if (g->snake.direction != DIR_RIGHT) g->snake.direction = DIR_LEFT; 
                break;
            case SDLK_RIGHT: 
                if (g->snake.direction != DIR_LEFT) g->snake.direction = DIR_RIGHT; 
                break;
        }
    }
}

void game_update(Game *game, float dt) {
    snake_update(&game->snake, dt);

    // Itération sécurisée pour la mise à jour et suppression éventuelle
    for (ListNode *node = game->trees.first; node != NULL;) {
        Tree *tree = (Tree *)node->data;
        node = node->next; // Avancer avant la mise à jour
        tree_update(tree, dt, game);
    }
    for (ListNode *node = game->apples.first; node != NULL;) {
        Apple *apple = (Apple *)node->data;
        node = node->next;
        apple_update(apple, dt, game);
    }
    for (ListNode *node = game->seeds.first; node != NULL;) {
        Seed *seed = (Seed *)node->data;
        node = node->next;
        seed_update(seed, dt, game);
    }

    // Collision serpent/pommes
    Vec2 *head_pos = (Vec2*)game->snake.body->first->data;
    for (ListNode *node = game->apples.first; node != NULL; node = node->next) {
        Apple* apple = (Apple*)node->data;
        if (apple->state == APPLE_FELL) {
            if (head_pos->x == apple->position.x && head_pos->y == apple->position.y) {
                apple_ingested(apple);
                snake_grow(&game->snake);
            }
        }
    }

    // Suivi de la caméra
    game->viewport_pos.x = head_pos->x - VIEWPORT_W / 2;
    game->viewport_pos.y = head_pos->y - VIEWPORT_H / 2;
}

void game_render(Game *g, SDL_Renderer *r) {
    SDL_SetRenderDrawColor(r, 20, 20, 20, 255);
    SDL_RenderClear(r);

    // 1. Dessiner le fond (herbe)
    int start_x = (int)(g->viewport_pos.x / TILE_SIZE);
    int start_y = (int)(g->viewport_pos.y / TILE_SIZE);
    int end_x = start_x + (VIEWPORT_W / TILE_SIZE) + 2;
    int end_y = start_y + (VIEWPORT_H / TILE_SIZE) + 2;

    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x) {
            SDL_FRect dest = {(float)x * TILE_SIZE - g->viewport_pos.x, 
                              (float)y * TILE_SIZE - g->viewport_pos.y, TILE_SIZE, TILE_SIZE};
            TileType grass_type = (x + y) % 2 == 0 ? TILE_GRASS_1 : TILE_GRASS_2;
            tileset_render_tile(&g->tileset, r, grass_type, &dest);
        }
    }

    // 2. Dessiner les arbres, pommes, graines
    TileType type;
    list_foreach(&(g->trees), node) {
        Tree *t = (Tree*)node->data;
        SDL_FRect dest = {t->position.x - g->viewport_pos.x, t->position.y - g->viewport_pos.y, TILE_SIZE, TILE_SIZE};
        switch(t->state) {
            case TREE_YOUNG:        type = TILE_TREE_YOUNG; break;
            case TREE_NORMAL:       type = TILE_TREE_NORMAL; break;
            case TREE_OLD:          type = TILE_TREE_OLD; break;
            case TREE_DEAD:         type = TILE_TREE_DEAD; break;
            default:                type = TILE_NONE; break;
        }
        tileset_render_tile(&g->tileset, r, type, &dest);
    }
    list_foreach(&(g->apples), node) {
        Apple *a = (Apple*)node->data;
        SDL_FRect dest = {a->position.x - g->viewport_pos.x, a->position.y - g->viewport_pos.y, TILE_SIZE, TILE_SIZE};
         switch(a->state) {
            case APPLE_FLOWER:      type = TILE_APPLE_FLOWER; break;
            case APPLE_RIPE:        type = TILE_APPLE_RIPE; break;
            case APPLE_FELL:        type = TILE_APPLE; break;
            case APPLE_INGESTED:    type = TILE_NONE; break;
            case APPLE_DIGESTED:    type = TILE_NONE; break; 
            case APPLE_ROTTED:      type = TILE_APPLE_ROTTED; break;
            case APPLE_DECOMPOSED:  type = TILE_APPLE_ROTTED; break;
            default:                type = TILE_NONE; break;
        }
        tileset_render_tile(&g->tileset, r, type, &dest);
    }
    list_foreach(&(g->seeds), node) {
        Seed *s = (Seed*)node->data;
        SDL_FRect dest = {s->position.x - g->viewport_pos.x, s->position.y - g->viewport_pos.y, TILE_SIZE, TILE_SIZE};
        tileset_render_tile(&g->tileset, r, TILE_SEED, &dest);
    }

    // 3. Dessiner le serpent (logique complexe)
    if (!g->snake.body->first) return;

    for (ListNode *node = g->snake.body->first; node; node = node->next) {
        Vec2 *pos = (Vec2 *)node->data;
        SDL_FRect dest = {pos->x - g->viewport_pos.x, pos->y - g->viewport_pos.y, TILE_SIZE, TILE_SIZE};

        if (node == g->snake.body->first) { // Tête
            switch (g->snake.direction) {
                case DIR_UP: type = TILE_SNAKE_HEAD_UP; break;
                case DIR_DOWN: type = TILE_SNAKE_HEAD_DOWN; break;
                case DIR_LEFT: type = TILE_SNAKE_HEAD_LEFT; break;
                case DIR_RIGHT: type = TILE_SNAKE_HEAD_RIGHT; break;
            }
        } else if (node == g->snake.body->last) { // Queue
            Vec2 *prev_pos = (Vec2 *)node->prev->data;
            if (pos->y < prev_pos->y) type = TILE_SNAKE_TAIL_UP;
            else if (pos->y > prev_pos->y) type = TILE_SNAKE_TAIL_DOWN;
            else if (pos->x < prev_pos->x) type = TILE_SNAKE_TAIL_LEFT;
            else type = TILE_SNAKE_TAIL_RIGHT;
        } else { // Corps
            Vec2 *prev_pos = (Vec2 *)node->prev->data;
            Vec2 *next_pos = (Vec2 *)node->next->data;

            if (prev_pos->x == next_pos->x) type = (pos->y < prev_pos->y) ? TILE_SNAKE_BODY_VERTICAL_UP : TILE_SNAKE_BODY_VERTICAL_DOWN;
            else if (prev_pos->y == next_pos->y) type = (pos->x < prev_pos->x) ? TILE_SNAKE_BODY_HORIZONTAL_LEFT : TILE_SNAKE_BODY_HORIZONTAL_RIGHT;
            else { // C'est un virage
                if      (prev_pos->x < pos->x && next_pos->y < pos->y) type = () ? TILE_SNAKE_BODY_ : TILE_SNAKE_BODY_ ;
                else if (prev_pos->x < pos->x && next_pos->y > pos->y) type = () ? TILE_SNAKE_BODY_ : TILE_SNAKE_BODY_ ;
                else if (prev_pos->x > pos->x && next_pos->y < pos->y) type = () ? TILE_SNAKE_BODY_ : TILE_SNAKE_BODY_ ;
                else if (prev_pos->x > pos->x && next_pos->y > pos->x) type = () ? TILE_SNAKE_BODY_ : TILE_SNAKE_BODY_ ;
            }
        }
        tileset_render_tile(&g->tileset, r, type, &dest);
    }
    
    SDL_RenderPresent(r);
}

void game_free(Game *game) {
    snake_free(&game->snake);
    list_clear(&game->trees, (void(*)(void*))tree_free);
    list_clear(&game->apples, (void(*)(void*))apple_free);
    list_clear(&game->seeds, (void(*)(void*))seed_free);
}