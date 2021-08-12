#include "engine/core/hashtable.h"
#include "engine/core/vector.h"
#include "engine/core/list.h"
#include "engine/core/log.h"
#include "engine/core/memory.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

static bool         hashtable__contains(const hashtable_t* table,
                                        const void* key,
                                        ssize_t* outi,
                                        ssize_t* outj);
static inline bool  hashtable__default_cmp(void* a, void* b);
static uint64_t     hashtable__hash(const void* key);

hashtable_t*
hashtable_create(size_t size, bool (*cmp)(void*, void*), void (*delete)(void*))
{
    hashtable_t* table = malloc(sizeof(*table));

    if (!table) {
        loge("Failed to create hashtable");
        return NULL;
    }

    vector_init_with(table->entries, size);

    if (!table->entries) {
        loge("Failed to create hashtable");
        free(table);
        return NULL;
    }

    table->cmp = cmp ? cmp : hashtable__default_cmp;
    table->delete = delete;

    return table;
}

void
hashtable_destroy(hashtable_t* table)
{
    for (size_t i = 0; i < vector_size(table->entries); ++i)
        vector_free(table->entries[i]);

    vector_free(table->entries);
}

size_t
hashtable_len(const hashtable_t* table)
{
    return vector_size(table);
}

void
hashtable_clear(hashtable_t* table)
{
    for (size_t i = 0; i < vector_size(table->entries); ++i)
        vector_clear(table->entries[i]);

    vector_clear(table->entries);
}

void
hashtable_insert(hashtable_t* table, const void* key, void* value)
{
    ssize_t i;
    if (hashtable__contains(table, key, &i, NULL))
        return;

    hashtable_entry_t entry = {key, value};

    /* A collision hasn't happend for this key yet, create a new vector */
    if (!table->entries[i]->key && !table->entries[i]->value)
        vector_init(table->entries[i]);

    vector_push(table->entries[i], entry);
}

void
hashtable_delete(hashtable_t* table, const void* key)
{
    ssize_t i, j;
    if (!hashtable__contains(table, key, &i, &j))
        return;

    if (table->delete)
        table->delete(table->entries[i][j].value);

    vector_delete(table->entries[i], j);
}

bool
hashtable_contains(const hashtable_t* table, const void* key)
{
    return hashtable__contains(table, key, NULL, NULL);
}

const void*
hashtable_find(const hashtable_t* table, const void* key)
{
    ssize_t i, j;
    if (!hashtable__contains(table, key, &i, &j))
        return;

    return (const void*)table->entries[i][j].value;
}


static bool
hashtable__contains(const hashtable_t* table, const void* key, ssize_t* outi, ssize_t* outj)
{
    size_t i = hashtable__hash(key) % vector_size(table->entries);

    if (!table->entries[i]) {
        if (outi) *outi = -1;
        if (outj) *outj = -1;
        return false;
    }

    for (size_t j = 0; j < vector_size(table->entries[i]); ++j) {
        if (table->cmp && table->cmp(table->entries[i][j].key, key)) {
            if (outi) *outi = i;
            if (outj) *outj = j;
            return true;
        }
    }

    return false;
}

static inline bool
hashtable__default_cmp(void* a, void* b)
{
    return a == b;
}

static uint64_t
hashtable__hash(const void* key)
{
    uint64_t hash = 0xcbf29ce484222325;
    unsigned char* str = key;

    for (; *str != 0; ++str) {
        hash ^= (uint64_t)(*str);
        hash *= 0x100000001b3;
    }

    return hash;
}
