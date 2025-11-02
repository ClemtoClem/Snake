#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "structs.h"

void list_init(List *list);
void list_push_front(List *list, void *data);
void list_push_back(List *list, void *data);
void list_remove(List *list, void *data);
void list_remove_node(List *list, ListNode *node);
void list_rotate(List *list);
void list_clear(List *list, void (*free_func)(void*));

#define list_foreach(list, node) \
    for (ListNode *node = (list)->first; node; node = node->next)

#endif // LIST_H
