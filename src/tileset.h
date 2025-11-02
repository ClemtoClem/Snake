#ifndef TILESET_H
#define TILESET_H

#include <SDL3/SDL.h>

// Énumération de toutes les tuiles possibles dans le jeu
typedef enum {
    TILE_NONE,

    // Fond
    TILE_GRASS_1,
    TILE_GRASS_2,

    // Serpent
    TILE_SNAKE_HEAD_UP,
    TILE_SNAKE_HEAD_DOWN,
    TILE_SNAKE_HEAD_LEFT,
    TILE_SNAKE_HEAD_RIGHT,
    TILE_SNAKE_TAIL_UP,
    TILE_SNAKE_TAIL_DOWN,
    TILE_SNAKE_TAIL_LEFT,
    TILE_SNAKE_TAIL_RIGHT,
    TILE_SNAKE_BODY_HORIZONTAL_LEFT,
    TILE_SNAKE_BODY_HORIZONTAL_RIGHT,
    TILE_SNAKE_BODY_VERTICAL_UP,
    TILE_SNAKE_BODY_VERTICAL_DOWN,
    TILE_SNAKE_BODY_RIGHT_TO_DOWN,
    TILE_SNAKE_BODY_UP_TO_RIGHT,
    TILE_SNAKE_BODY_LEFT_TO_UP,
    TILE_SNAKE_BODY_DOWN_TO_LEFT,
    TILE_SNAKE_BODY_DOWN_TO_RIGHT,
    TILE_SNAKE_BODY_LEFT_TO_DOWN,
    TILE_SNAKE_BODY_UP_TO_LEFT,
    TILE_SNAKE_BODY_RIGHT_TO_UP,

    // Pommes
    TILE_APPLE_FLOWER,
    TILE_APPLE_RIPE,
    TILE_APPLE_FELL,
    TILE_APPLE_ROTTED,
    TILE_APPLE,

    // Graine
    TILE_SEED,
    
    // Arbres
    TILE_TREE_YOUNG,
    TILE_TREE_NORMAL,
    TILE_TREE_OLD,
    TILE_TREE_DEAD,
    
    // Compteur
    TILE_TYPE_COUNT 
} TileType;

// Structure contenant la texture du tileset et la map des rectangles sources
typedef struct {
    SDL_Texture *texture;
    SDL_FRect rects[TILE_TYPE_COUNT];
} Tileset;

// Initialise le tileset en chargeant l'image et en définissant les rectangles
bool tileset_init(Tileset *ts, SDL_Renderer *renderer, const char *image_path);

// Libère la texture du tileset
void tileset_free(Tileset *ts);

// Affiche une tuile à une position de destination
void tileset_render_tile(Tileset *ts, SDL_Renderer *renderer, TileType type, const SDL_FRect *dest);

#endif // TILESET_H