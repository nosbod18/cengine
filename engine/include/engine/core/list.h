/**
 * list.h
 *
 * @brief A simple singley linked list implementated using recursion
 */

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include <stddef.h>

typedef struct list_t list_t;

/** Frees every node in the list, running free_fn on each element if it's not NULL */
void     list_destroy(list_t** head, void (*free_fn)(void* element));

/** Duplicates a list and returns a pointer to the new list or NULL on failure */
list_t*  list_dup(list_t* head);

/** Returns the node 'target' is in, or NULL if 'target' is not in the list */
list_t*  list_find(list_t* head, void* target);

/** Inserts a node at the beginning of a list */
void     list_prepend(list_t** head, void* data);

/** Inserts a node at the end of a list */
void     list_push(list_t** head, void* data);

/** Removes the last node from a list and returns its data */
void*    list_pop(list_t** head);

/** Gets the length of a list */
size_t   list_len(list_t* head);

/** Prints each node in a list, its data, and its next pointer */
void     list_print(list_t* head);

/** Just like list_print but prints the nodes in reverse */
void     list_print_reverse(list_t* head);


#endif /* CORE_LIST_H */
