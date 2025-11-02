#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake Garden", VIEWPORT_W, VIEWPORT_H, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    srand((unsigned int)time(NULL));
    Game game;
    game_init(&game, renderer);

    Uint64 last_ticks = SDL_GetTicks();
    int running = 1;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = 0;
            game_input(&game, &e);
        }

        Uint64 now = SDL_GetTicks();
        float delta = (now - last_ticks);
        last_ticks = now;

        game_update(&game, delta);
        game_render(&game, renderer);

        SDL_Delay(16); // ~60 FPS
    }

    game_free(&game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}