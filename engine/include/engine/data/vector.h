/**
 * vector.h
 *
 * @brief A dynamically allocated, packed array that can be used with a plain
 *  pointer of any type. Access into the vector is just like a normal array.
 *
 * The vector stores 2 elements of meta-data in front of the user pointer, which
 * contain the current allocated count and the current element count.
 *
 * NOTE: These functions all assume the pointers to be valid,
 *  i.e. they have been passed into vector_init
 *
 * NOTE: Any functions prefixed with vector__ (two underscores) are meant for internal
 * use and should not be called by the user
 *
 * Functions:
 *              vector_init(vec_, n_)
 *              vector_init_to(vec_)
 *              vector_free(vec_)
 *              vector_size(vec_)
 *
 *              vector_capacity(vec_)
 *              vector_full(vec_)
 *              vector_empty(vec_)
 *              vector_fill(vec_, val_)
 *
 *              vector_clear(vec_, fn_)
 *              vector_reserve(vec_, n_)
 *              vector_fit(vec_)
 *              vector_swap(vec_, i1_, i2_)
 *
 *              vector_begin(vec_)
 *              vector_end(vec_)
 *              vector_last(vec_)
 *
 *              vector_push(vec_, val_)
 *              vector_push_n(vec_, n_)
 *              vector_pop(vec_)
 *              vector_insert(vec_, i_, val_)
 *              vector_remove(vec_, i_)
 *
 *              vector_cat(vec1_, vec2_)
 *              vector_copy(vec1_, vec2_)
 *
 *              vector_sort(vec_, fn_)
 *              vector_foreach(vec_, i_, ...)
 */

#ifndef __DATA_VECTOR_H__
#define __DATA_VECTOR_H__

#include "engine/core/memory.h"
#include <stddef.h> /* size_t */

#define VECTOR__DEFAULT_SIZE 8

/** Initializes or resizes v with n elements of size type_size */
void*   vector__resize(void* v, size_t n, size_t type_size);

#define vector__grow_maybe(v_)      (!(v_) || vector_size(v_) > vector_capacity(v_)\
                                    ? ((v_) = vector__resize(v_, vector_size(v_) << 1, sizeof(*(v_))), 0) : 0)

#define vector__shrink_maybe(v_)    (!(v_) || (vector_size(v_) && vector_size(v_) < vector_capacity(v_) >> 2)\
                                    ? ((v_) = vector__resize(v_, vector_capacity(v_) >> 1, sizeof(*(v_))), 0) : 0)

#define vector_init(v_)             vector_init_with(v_, 8)
#define vector_init_with(v_, n_)    ((v_) = NULL, (v_) = vector__resize(v_, n_, sizeof(*(v_))))
#define vector_free(v_)             free((size_t*)(v_) - 2)

#define vector_capacity(v_)         (((size_t*)(v_))[-2])
#define vector_size(v_)             (((size_t*)(v_))[-1])
#define vector_full(v_)             (vector_size(v_) == vector_capacity(v_))
#define vector_empty(v_)            (vector_size(v_) == 0)

#define vector_begin(v_)            (v_)
#define vector_end(v_)              ((v_) + vector_size(v_))
#define vector_last(v_)             ((v_)[vector_size(v_) - 1])

#define vector_reserve(v_, n_)      ((n_) > vector_capacity(v_)\
                                    ? ((v_) = vector__resize((v_), (n_), sizeof(*(v_))), 0) : 0)

#define vector_insert(v_, i_, val_) (*vector_insert_n(v_, i_, 1) = (val_))
#define vector_delete(v_, i_)       (vector_delete_n(v_, i_, 1))
#define vector_push(v_, val_)       (*vector_push_n(v_, 1) = (val_))
#define vector_push_n(v_, n_)       (vector_insert_n(v_, vector_size(v_), n_))
#define vector_pop(v_)              (vector__shrink_maybe(v_), (v_)[--vector_size(v_)])

#define vector_insert_n(v_, i_, n_) (vector__grow_maybe(v_),\
                                     memmove((v_) + (i_) + (n_), (v_) + (i_), (vector_size(v_) - (i_) - (n_)) * sizeof(*(v_))),\
                                     vector_size(v_)+=(n_),\
                                     (v_) + (i_))

#define vector_delete_n(v_, i_, n_) (vector__shrink_maybe(v_),\
                                     memmove((v_) + (i_), (v_) + (i_) + (n_), (vector_size(v_) - (i_) - (n_)) * sizeof(*(v_))),\
                                     vector_size(v_)-=(n_))

#endif /* __DATA_VECTOR_H__ */
