#ifndef GAME_H
#define GAME_H

#include "structs.h"
#include <SDL3/SDL.h>

#define WORLD_SIZE_W 2000
#define WORLD_SIZE_H 2000
#define VIEWPORT_W 1000
#define VIEWPORT_H 1000

// La taille d'une tuile logique dans le monde du jeu
#define TILE_SIZE 32

void game_init(Game *game, SDL_Renderer *renderer);
void game_free(Game *game);
void game_input(Game *game, SDL_Event *e);
void game_update(Game *game, float delta);
void game_render(Game *game, SDL_Renderer *renderer);

#endif /* GAME_H */