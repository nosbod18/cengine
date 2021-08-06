/**
 * list.h
 *
 * @brief A simple singley linked list implementated using recursion
 */

#ifndef __DATA_LIST_H__
#define __DATA_LIST_H__

#include <stddef.h>

typedef struct list_t list_t;

/** Frees every node in the list, running free_fn on each element if it's not NULL */
void     list_destroy(list_t** head, void (*free_fn)(void* element));

/** Duplicates a list and returns a pointer to the new list or NULL on failure */
list_t*  list_dup(list_t* head);

/** Returns the node 'target' is in, or NULL if 'target' is not in the list */
list_t*  list_find(list_t* head, void* target);

/** Inserts 'data' at the end of 'head' */
void     list_push(list_t** head, void* data);

/** Removes the last node from the list and returns its data */
void*    list_pop(list_t** head);

/** Gets the length of a list */
size_t   list_length(list_t* head);

/** Prints each node in a list, its data, and its next pointer */
void     list_print(list_t* head);

/** Just like list_print but prints the nodes in reverse */
void     list_print_reverse(list_t* head);


#endif /* __DATA_LIST_H__ */
