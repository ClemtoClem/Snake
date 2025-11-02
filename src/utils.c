// @file ./src/sdl_util.c
#include <SDL3/SDL.h>
#include <math.h>

void SDL_RenderCircle(SDL_Renderer *r, int x0, int y0, int radius) {
    for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderPoint(r, x0 + dx, y0 + dy);
            }
        }
    }
}
