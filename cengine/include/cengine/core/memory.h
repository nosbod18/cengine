#ifndef _CE_CORE_MEMORY_H_
#define _CE_CORE_MEMORY_H_

#include "cengine/core/base.h"

void ce_memInit(void);
void ce_memExit(void);

#define ce_malloc(size_)            ce__malloc(size_ CE_DEBUG_PARAMS_IMP);
#define ce_calloc(count_, size_)    ce__calloc(count_, size_ CE_DEBUG_PARAMS_IMP);
#define ce_realloc(ptr_, size_)     ce__realloc(ptr_, size_ CE_DEBUG_PARAMS_IMP);
#define ce_free(ptr_)               ce__free(ptr_ CE_DEBUG_PARAMS_IMP);

void*   ce__malloc(size_t size CE_DEBUG_PARAMS_DEF);
void*   ce__calloc(size_t count, size_t size CE_DEBUG_PARAMS_DEF);
void*   ce__realloc(void* ptr, size_t size CE_DEBUG_PARAMS_DEF);
void    ce__free(void* ptr CE_DEBUG_PARAMS_DEF);

#endif /* _CE_CORE_MEMORY_H_ */
