#include "snake.h"
#include "list.h"
#include "game.h"
#include "timer.h"
#include <stdlib.h>
#include <string.h>

#define SNAKE_MOVE_TIME 100.0f // ms

// Helper to free Vec2 pointers stored in the list
void free_vec2(void *data) {
    free(data);
}

void snake_init(Snake *snake) {
    snake->body = malloc(sizeof(List));
    list_init(snake->body);
    snake->direction = DIR_RIGHT;
    snake->state = SNAKE_MOVING;
    snake->pending_growth = 0;
    timer_init(&snake->timer, SNAKE_MOVE_TIME, true);
    snake_reset(snake);
}

void snake_reset(Snake *snake) {
    list_clear(snake->body, free_vec2);
    
    snake->direction = DIR_RIGHT;
    snake->pending_growth = 3; // Start with a body of 4 segments

    Vec2 *head = malloc(sizeof(Vec2));
    head->x = WORLD_SIZE_W / 2;
    head->y = WORLD_SIZE_H / 2;
    list_push_front(snake->body, head);
}


void snake_update(Snake *snake, float dt) {
    if (snake->state != SNAKE_MOVING) return;

    if (timer_update(&snake->timer, dt)) {
        Vec2 *current_head_pos = (Vec2*)snake->body->first->data;
        Vec2 *new_head_pos = malloc(sizeof(Vec2));
        *new_head_pos = *current_head_pos;

        // Move head
        switch (snake->direction) {
            case DIR_UP:    new_head_pos->y -= TILE_SIZE; break;
            case DIR_DOWN:  new_head_pos->y += TILE_SIZE; break;
            case DIR_LEFT:  new_head_pos->x -= TILE_SIZE; break;
            case DIR_RIGHT: new_head_pos->x += TILE_SIZE; break;
        }
        
        // World wrapping
        if (new_head_pos->x < 0) new_head_pos->x = WORLD_SIZE_W - TILE_SIZE;
        if (new_head_pos->x >= WORLD_SIZE_W) new_head_pos->x = 0;
        if (new_head_pos->y < 0) new_head_pos->y = WORLD_SIZE_H - TILE_SIZE;
        if (new_head_pos->y >= WORLD_SIZE_H) new_head_pos->y = 0;

        // Self collision check
        list_foreach(snake->body, node) {
            if (node == snake->body->last) continue; // Don't check against the tail that will move
            Vec2 *part = (Vec2*)node->data;
            if (part->x == new_head_pos->x && part->y == new_head_pos->y) {
                snake_reset(snake);
                free(new_head_pos);
                return;
            }
        }

        list_push_front(snake->body, new_head_pos);

        if (snake->pending_growth > 0) {
            snake->pending_growth--;
        } else {
            ListNode *tail_node = snake->body->last;
            free(tail_node->data);
            list_remove_node(snake->body, tail_node);
        }
    }
}

void snake_grow(Snake *snake) {
    snake->pending_growth++;
}

void snake_free(Snake *snake) {
    list_clear(snake->body, free_vec2);
    free(snake->body);
}