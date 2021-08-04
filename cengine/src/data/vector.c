#include "cengine/data/vector.h"
#include "cengine/core/memory.h"

void
ce__vectorResize(size_t** vec_ptr, size_t n, size_t type_size)
{
    const size_t size = (sizeof(size_t) * 2) + (n * type_size);
    size_t* new_vec = NULL;

    if (!(*vec_ptr)) {
        new_vec = ce_calloc(1, size);
        if (!new_vec)return;

        new_vec[1] = n;
    } else {
        new_vec = ce_realloc(*vec_ptr, size);
        if (!new_vec) return;

        new_vec[1] = (*vec_ptr)[1];
    }

    new_vec[0] = n;
    (*vec_ptr) = (void*)(new_vec + 2);
}
