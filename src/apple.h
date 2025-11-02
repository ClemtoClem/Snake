#ifndef APPLE_H
#define APPLE_H

#include "structs.h"

#define APPLE_GERMINATE_TIME        240
#define APPLE_FELL_TIME             20
#define APPLE_ROTTING_TIME          50
#define APPLE_DECOMPOSITION_TIME    20
#define APPLE_DIGESTION_TIME        30

Apple *apple_create(Vec2 pos);
void apple_update(Apple *apple, float dt, Game *game);
void apple_ingested(Apple *apple);
void apple_free(Apple *apple);

#endif // APPLE_H
