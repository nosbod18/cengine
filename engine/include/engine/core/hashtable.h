#ifndef __CORE_HASHTABLE_H__
#define __CORE_HASHTABLE_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct hashtable_entry_t
{
    const void* key;
    void* value;
} hashtable_entry_t;

typedef struct hashtable_t
{
    hashtable_entry_t** entries;
    int collisions;

    bool (*cmp)(void*, void*);
    void (*delete)(void*);
} hashtable_t;

hashtable_t*    hashtable_create(size_t size, bool (*cmp)(void*, void*), void (*delete)(void*));
void            hashtable_destroy(hashtable_t* table);

size_t          hashtable_len(const hashtable_t* table);

void            hashtable_clear(hashtable_t* table);

void            hashtable_insert(hashtable_t* table, const void* key, void* value);
void            hashtable_delete(hashtable_t* table, const void* key);

bool            hashtable_contains(const hashtable_t* table, const void* key);
const void*     hashtable_find(const hashtable_t* table, const void* key);

#endif /* __CORE_HASHTABLE_H__ */
