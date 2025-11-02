#include "tileset.h"
#include <stdio.h>
#include <SDL3_image/SDL_image.h>

// Taille d'une tuile en pixels
#define TILE_GFX_SIZE 32

#define TILE_RECT(x, y) (SDL_FRect){x * TILE_GFX_SIZE, y * TILE_GFX_SIZE, TILE_GFX_SIZE, TILE_GFX_SIZE}

bool tileset_init(Tileset *ts, SDL_Renderer *renderer, const char *image_path) {
    ts->texture = IMG_LoadTexture(renderer, image_path);
    if (!ts->texture) {
        printf("Failed to load tileset image: %s\n", SDL_GetError());
        return false;
    }

    // Position de chaque tuile dans l'image
    // Herbe
    ts->rects[TILE_GRASS_1]                     = TILE_RECT(4,0);
    ts->rects[TILE_GRASS_2]                     = TILE_RECT(5,0);

    // Serpent (l'image change en fonction du sens de déplacement)
    ts->rects[TILE_SNAKE_HEAD_UP]               = TILE_RECT(2,0);
    ts->rects[TILE_SNAKE_HEAD_DOWN]             = TILE_RECT(3,0);
    ts->rects[TILE_SNAKE_HEAD_LEFT]             = TILE_RECT(4,0);
    ts->rects[TILE_SNAKE_HEAD_RIGHT]            = TILE_RECT(5,0);
    
    ts->rects[TILE_SNAKE_TAIL_DOWN]             = TILE_RECT(6,0);
    ts->rects[TILE_SNAKE_TAIL_UP]               = TILE_RECT(7,0);
    ts->rects[TILE_SNAKE_TAIL_LEFT]             = TILE_RECT(8,0);
    ts->rects[TILE_SNAKE_TAIL_RIGHT]            = TILE_RECT(9,0);

    ts->rects[TILE_SNAKE_BODY_VERTICAL_UP]      = TILE_RECT(6,1);
    ts->rects[TILE_SNAKE_BODY_VERTICAL_DOWN]    = TILE_RECT(7,1);
    ts->rects[TILE_SNAKE_BODY_HORIZONTAL_LEFT]  = TILE_RECT(8,1);
    ts->rects[TILE_SNAKE_BODY_HORIZONTAL_RIGHT] = TILE_RECT(9,1);
    
    // Virage
    ts->rects[TILE_SNAKE_BODY_RIGHT_TO_DOWN]    = TILE_RECT(0,3);
    ts->rects[TILE_SNAKE_BODY_UP_TO_RIGHT]      = TILE_RECT(0,4);
    ts->rects[TILE_SNAKE_BODY_LEFT_TO_UP]       = TILE_RECT(1,4);
    ts->rects[TILE_SNAKE_BODY_DOWN_TO_LEFT]     = TILE_RECT(1,3);

    ts->rects[TILE_SNAKE_BODY_DOWN_TO_RIGHT]    = TILE_RECT(1,3);
    ts->rects[TILE_SNAKE_BODY_LEFT_TO_DOWN]     = TILE_RECT(2,3);
    ts->rects[TILE_SNAKE_BODY_UP_TO_LEFT]       = TILE_RECT(2,4);
    ts->rects[TILE_SNAKE_BODY_RIGHT_TO_UP]      = TILE_RECT(1,4);
    
    // Pommes et Graine
    ts->rects[TILE_APPLE_FLOWER]                = TILE_RECT(6,0);
    ts->rects[TILE_APPLE_RIPE]                  = TILE_RECT(6,1);
    ts->rects[TILE_APPLE_FELL]                  = TILE_RECT(6,2);
    ts->rects[TILE_APPLE_ROTTED]                = TILE_RECT(6,3);
    ts->rects[TILE_SEED]                        = TILE_RECT(6,4);

    // Arbres
    ts->rects[TILE_TREE_YOUNG]                  = TILE_RECT(4,1);
    ts->rects[TILE_TREE_NORMAL]                 = TILE_RECT(4,2);
    ts->rects[TILE_TREE_OLD]                    = TILE_RECT(4,3);
    ts->rects[TILE_TREE_DEAD]                   = TILE_RECT(4,4);

    return true;
}

void tileset_free(Tileset *ts) {
    if (ts->texture) {
        SDL_DestroyTexture(ts->texture);
        ts->texture = NULL;
    }
}

void tileset_render_tile(Tileset *ts, SDL_Renderer *renderer, TileType type, const SDL_FRect *dest) {
    if (type >= TILE_TYPE_COUNT || type == TILE_NONE) return;
    SDL_RenderTexture(renderer, ts->texture, &ts->rects[type], dest);
}