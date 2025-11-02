#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void list_init(List *list) {
    list->first = list->last = NULL;
    list->count = 0;
}

void list_push_front(List *list, void *data) {
    ListNode *node = malloc(sizeof(ListNode));
    node->data = data;
    node->prev = NULL;
    node->next = list->first;

    if (list->first) {
        list->first->prev = node;
    } else {
        list->last = node;
    }
    list->first = node;
    list->count++;
}

void list_push_back(List *list, void *data) {
    ListNode *node = malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    node->prev = list->last;

    if (list->last) {
        list->last->next = node;
    } else {
        list->first = node;
    }
    list->last = node;
    list->count++;
}


void list_remove(List *list, void *data) {
    for (ListNode *node = list->first; node; node = node->next) {
        if (node->data == data) {
            list_remove_node(list, node);
            break;
        }
    }
}

void list_remove_node(List *list, ListNode *node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        list->first = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->last = node->prev;

    free(node);
    list->count--;
}


void list_clear(List *list, void (*free_func)(void *)) {
    ListNode *node = list->first;
    while (node) {
        ListNode *next = node->next;
        if (free_func)
            free_func(node->data);
        free(node);
        node = next;
    }
    list->first = list->last = NULL;
    list->count = 0;
}