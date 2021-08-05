#define MEMORY_RECURSION_GUARD
#include "cengine/core/memory.h"
#include "cengine/core/log.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct mem_entry__t
{
    size_t size;
    uintptr_t address;

#ifndef MEMORY_LOW_FOOTPRINT
    const char* file;
    const char* func;
    const int   line;
#endif
} mem_entry__t;

static struct
{
    size_t total;
    size_t current;
    size_t peak;

    int failed;
    int mallocs;
    int callocs;
    int reallocs;
    int frees;
} gStats = {0};


static void mem__exit(void);

void
mem_init(void)
{
    atexit(mem__exit);
}

static void
mem__exit(void)
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

    printf("Failed allocations: %5d\n", gStats.failed);
    printf("Malloc calls:  %5d\n", gStats.mallocs);
    printf("Calloc calls:  %5d\n", gStats.callocs);
    printf("Realloc calls: %5d\n", gStats.reallocs);
    printf("Free calls:    %5d\n", gStats.frees);

    printf("\n---------------------------------------\n");
}

void*
mem__alloc(size_t size, const char* file, int line, const char* func)
{
    if (!size) {
        logw("Tried to allocate a block of size 0. Adjusting size...");
        size = 1;
    }

    mem_entry__t* mem = malloc(size + sizeof(*mem));

    if (!(mem)) {
        loge("Could not allocate %zu B", size);
        gStats.failed += 1;
        return NULL;
    }

    mem_entry__t tmp = {
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
mem__calloc(size_t count, size_t size, const char* file, int line, const char* func)
{
    if (!size) {
        logw("Tried to allocate a block of size 0. Adjusting size...");
        size = 1;
    }

    if (!count) {
        logw("Tried to allocate a block of size 0. Adjusting size...");
        count = 1;
    }

    mem_entry__t* mem = calloc(1, count * size + sizeof(*mem));

    if (!(mem)) {
        loge("Could not allocate %zu B", count * size);
        gStats.failed += 1;
        return NULL;
    }

    mem_entry__t tmp = {
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
mem__realloc(void* ptr, size_t size, const char* file, int line, const char* func)
{
    if (!size) {
        logw("Tried to allocate a block of size 0. Adjusting size...");
        size = 1;
    }

    mem_entry__t* head = (mem_entry__t*)ptr - 1;
    mem_entry__t* mem = realloc(head, size + sizeof(*mem));

    if (!(mem)) {
        loge("Could not allocate %zu B", size);
        gStats.failed += 1;
        return ptr;
    }

    mem_entry__t tmp = {
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
mem__free(void* ptr, const char* file, int line, const char* func)
{
    UNUSED(file); UNUSED(line); UNUSED(func);

    if (!ptr)
        return;

    mem_entry__t* head = (mem_entry__t*)ptr - 1;

    gStats.current -= head->size;

    free(head);
    head = NULL;
}

