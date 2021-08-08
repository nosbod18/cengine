/**
 * @file memory.h
 *
 * @brief A basic wrapper around the memory managment functions which provides
 *        helpful info such as memory leaks and error checking
 *
 * NOTE: define MEMORY_LOW_FOOTPRINT to make this module use less extra memory per
 *       allocation
 */

#ifndef __CORE_MEMORY_H__
#define __CORE_MEMORY_H__

#include "engine/core/base.h"

#ifdef MEMORY_LOW_FOOTPRINT
    #define MEM_DEBUG_PARAMS_DEF
    #define MEM_DEBUG_PARAMS_IMPL
#else
    #define MEM_DEBUG_PARAMS_DEF  , const char* file, int line, const char* func
    #define MEM_DEBUG_PARAMS_IMPL , FILENAME, __LINE__, __func__
#endif

void memory_init(void);

/* To avoid recursive expansions the actual memory functions */
#ifndef MEMORY_RECURSION_GUARD
    #define malloc(size_)           mem__alloc(size_ MEM_DEBUG_PARAMS_IMPL)
    #define calloc(count_, size_)   mem__calloc(count_, size_ MEM_DEBUG_PARAMS_IMPL)
    #define realloc(ptr_, size_)    mem__realloc(ptr_, size_ MEM_DEBUG_PARAMS_IMPL)
    #define free(ptr_)              mem__free(ptr_ MEM_DEBUG_PARAMS_IMPL)
#endif /* MEMORY_RECURSION_GUARD */

void*   mem__alloc(size_t size MEM_DEBUG_PARAMS_DEF);
void*   mem__calloc(size_t count, size_t size MEM_DEBUG_PARAMS_DEF);
void*   mem__realloc(void* ptr, size_t size MEM_DEBUG_PARAMS_DEF);
void    mem__free(void* ptr MEM_DEBUG_PARAMS_DEF);

#endif /* __CORE_MEMORY_H__ */
