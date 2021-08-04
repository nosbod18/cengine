#include "cengine/core/memory.h"
#include "cengine/core/log.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct ce__MemEntry
{
    size_t size;

    uintptr_t address;
    const char* file;
    const char* func;
    const int   line;
} ce__MemEntry;

static struct
{
    size_t total;
    size_t current;
    size_t peak;

    int mallocs;
    int callocs;
    int reallocs;
    int frees;
} gStats = {0};

void
ce_memInit(void)
{
    atexit(ce_memExit);
}

void
ce_memExit(void)
{
    printf("---------------------------------------\n");
    printf("---------- MEMORY STATISTICS ----------\n");
    printf("---------------------------------------\n\n");

    printf("Total allocated: %20zu B (%.3f MB)\n",
        gStats.total, (double)gStats.total / 1000000.0);

    printf("Peak memory usage: %20zu B (%.3f MB)",
        gStats.peak, (double)gStats.peak / 1000000.0);

    printf("Leaked memory: %20zu B (%.3f MB)\n\n",
        gStats.current, (double)gStats.current / 1000000.0);

    printf("Malloc calls:  %5d\n", gStats.mallocs);
    printf("Calloc calls:  %5d\n", gStats.callocs);
    printf("Realloc calls: %5d\n", gStats.reallocs);
    printf("Free calls:    %5d\n", gStats.frees);

    printf("\n---------------------------------------\n");
}

void*
ce__malloc(size_t size CE_DEBUG_PARAMS_DEF)
{
    if (!size)
        size = 1;

    ce__MemEntry* mem = malloc(size + sizeof(*mem));

    if (!(mem)) {
        ce_error("Could not allocate %zu B", size);
        return NULL;
    }

    ce__MemEntry tmp = {
        size, (uintptr_t)(mem + 1), file, func, line
    };

    memcpy(mem, &tmp, size + sizeof(*mem));

    gStats.total += size;
    gStats.current += size;

    if (gStats.current > gStats.peak)
        gStats.peak = gStats.current;

    gStats.mallocs += 1;

    return (void*)(mem + 1);
}

void*
ce__calloc(size_t count, size_t size CE_DEBUG_PARAMS_DEF)
{
    if (!size)
        size = 1;

    if (!count)
        count = 1;

    ce__MemEntry* mem = calloc(1, count * size + sizeof(*mem));

    if (!(mem)) {
        ce_error("Could not allocate %zu B", count * size);
        return NULL;
    }

    ce__MemEntry tmp = {
        count * size, (uintptr_t)(mem + 1), file, func, line
    };

    memcpy(mem, &tmp, size + sizeof(*mem));

    gStats.total += size;
    gStats.current += size;

    if (gStats.current > gStats.peak)
        gStats.peak = gStats.current;

    gStats.callocs += 1;

    return (void*)(mem + 1);
}

void*
ce__realloc(void* ptr, size_t size CE_DEBUG_PARAMS_DEF)
{
    if (!size)
        size = 1;

    ce__MemEntry* head = (ce__MemEntry*)ptr - 1;
    ce__MemEntry* mem = realloc(head, size + sizeof(*mem));

    if (!(mem)) {
        ce_error("Could not allocate %zu B", size);
        return ptr;
    }

    ce__MemEntry tmp = {
        size, (uintptr_t)(mem + 1), file, func, line
    };

    memcpy(mem, &tmp, size + sizeof(*mem));

    gStats.total += size - head->size;
    gStats.current += size - head->size;

    if (gStats.current > gStats.peak)
        gStats.peak = gStats.current;

    gStats.reallocs += 1;

    return (void*)(mem + 1);
}

void
ce__free(void* ptr CE_DEBUG_PARAMS_DEF)
{
    if (!ptr)
        return;

    ce__MemEntry* head = (ce__MemEntry*)ptr - 1;

    gStats.current -= head->size;

    free(head);
    head = NULL;
}

