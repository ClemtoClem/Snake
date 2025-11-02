#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL3/SDL.h>
#include "tileset.h"

typedef struct Vec2 { float x; float y; } Vec2;
typedef struct Vec3 { float x; float y; float z; } Vec3;
typedef struct Size { float w; float h; } Size;
typedef struct Rect { float x; float y; float w; float h; } Rect;

typedef struct ListNode ListNode;
struct ListNode {
    void *data;
    ListNode *prev;
    ListNode *next;
};

typedef struct List {
    ListNode *first;
    ListNode *last;
    Uint64 count;
} List;

typedef struct Timer {
    float current;
    float interval;
    bool loop;
} Timer;

typedef enum TreeState {
    TREE_YOUNG,
    TREE_NORMAL,
    TREE_OLD,
    TREE_DEAD
} TreeState;

typedef struct Tree {
    Vec2      position;
    int       age; // de 0 (jeune) à 100 (mature)
    float     radius;
    Timer     timer;
    TreeState state;
} Tree;

typedef struct Seed {
    Vec2  position;
    Timer timer; // timer pour donner un arbre
} Seed;

typedef enum AppleState {
    APPLE_FLOWER,
    APPLE_RIPE,      // Flower -> Ripe
    APPLE_FELL,      // Ripe -> Fell
    APPLE_INGESTED,
    APPLE_DIGESTED,  // Ingested -> Digested -> Seed
    APPLE_ROTTED,    // Normal -> Rotted -> Rotted Apple
    APPLE_DECOMPOSED // Rotted -> Decomposed -> Seed
} AppleState;

typedef struct Apple {
    Vec2       position;
    Timer      timer;
    AppleState state;
} Apple;


typedef enum Direction {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef enum SnakeState {
    SNAKE_PENDING,
    SNAKE_MOVING,
} SnakeState;

typedef struct Snake {
    List      *body; // tableau dynamique de Vec2
    Direction  direction;
    Timer      timer;
    SnakeState state;
    int pending_growth;
} Snake;

// Structure principale du jeu
typedef struct Game {
    Snake snake;

    List trees;
    List apples;
    List seeds;

    Vec2 viewport_pos;
    Tileset tileset;
} Game;

#endif /* STRUCTS_H */