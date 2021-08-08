#include "engine/data/list.h"
#include "engine/core/memory.h"

#include <stdio.h>
#include <stddef.h>

struct list_t
{
    void* data;
    list_t* next;
};

static list_t* list__create_node(void* data, list_t* next);
static void*   list__destroy_node(list_t* node);

void
list_destroy(list_t** head, void (*free_fn)(void* data))
{
    if (!(*head))
        return;

    list_destroy(&(*head)->next, free_fn);

    if (free_fn)
        free_fn(list__destroy_node(*head));
    else
        (void)list__destroy_node(*head);
}

list_t*
list_dup(list_t* head)
{
    if (!head)
        return NULL;
    else
        return list__create_node(head->data, list_dup(head->next));
}

list_t*
list_find(list_t* head, void* target)
{
    if (!head || head->data == target)
        return head;
    else
        return list_find(head->next, target);
}

void
list_push(list_t** head, void* data)
{
    if (!(*head))
        (*head) = list__create_node(data, NULL);
    else
        list_push(&(*head)->next, data);
}

void*
list_pop(list_t** head)
{
    if (!(*head))
        return NULL;
    else if (!(*head)->next)
        return list__destroy_node(*head);
    else
        return list_pop(&(*head)->next);
}

size_t
list_length(list_t* head)
{
    size_t i = 0;
    for ( ; head != NULL; ++i)
        head = head->next;
    return i;
}

void
list_print(list_t* head)
{
    if (!head)
        return;

    printf("Node %p:\n", (void*)head);
    printf("   data: %p\n", (void*)head->data);
    printf("   next: %p\n", (void*)head->next);

    list_print(head->next);
}

void
list_print_reverse(list_t* head)
{
    if (!head)
        return;

    list_print_reverse(head->next);

    printf("Node %p:\n", (void*)head);
    printf("   data: %p\n", (void*)head->data);
    printf("   next: %p\n", (void*)head->next);
}


static list_t*
list__create_node(void* data, list_t* next)
{
    list_t* list = malloc(sizeof(*list));

    if (list)
        *list = (list_t){data, next};

    return list;
}

static void*
list__destroy_node(list_t* node)
{
    void* data = node->data;
    free(node);
    return data;
}
