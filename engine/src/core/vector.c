#include "engine/core/vector.h"
#include "engine/core/memory.h"

void*
vector__resize(void* v, size_t n, size_t type_size)
{
    size_t* v_new = NULL;
    const size_t size = (sizeof(size_t) * 2) + (n * type_size);

    if (!v) {
        v_new = calloc(1, size);

        if (!v_new)
            return NULL;

    } else {
        size_t* v_old = (size_t*)v - 2;

        v_new = realloc(v_old, size);

        if (!v_new)
            return NULL;

        v_new[1] = v_old[1];
    }

    v_new[0] = n;
    return (void*)(v_new + 2);
}
