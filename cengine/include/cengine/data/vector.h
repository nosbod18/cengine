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

#include "cengine/core/memory.h"
#include <stddef.h> /* size_t */

#define VECTOR__DEFAULT_SIZE 8

/** Initializes or resizes *vec_ptr with n elements of size type_size */
void vector__resize(size_t** vec_ptr, size_t n, size_t type_size);

#define vector__head(vec_)\
    ((size_t*)(vec_) - 2)

/** Doubles the capacity of a vector if it's full */
#define vector__grow(vec_)                              \
    (vector_size(vec_) >= vector_capacity(vec_)         \
    ? vector__resize(&vector__head(vec_),               \
                    vector_capacity(vec_) << 1,         \
                    sizeof(*vec_))                      \
    : (void)0)


/** Halves the capacity of a vector if its size is less than 1/4 its capacity */
#define vector__shrink(vec_)                            \
    (vector_size(vec_) <= vector_capacity(vec_) >> 2    \
    ? vector__resize(&vector__head(vec_),               \
                    vector_capacity(vec_) >> 1,         \
                    sizeof(*vec_))                      \
    : (void)0)


/** Initializes a vector vec_ with n_ elements to start */
#define vector_init(vec_, n_)       \
    ((vec_) = NULL,                 \
    vector__resize(vec_, n_, sizeof(vec_)))


/** Initializes a vector vec_ with n_ elements to start and fills it with val_ */
#define vector_init_to(vec_, n_, val_)  \
    (vector_init(vec_, n_),             \
    vector_fill(vec_, val_))            \


/** Frees a vector */
#define vector_free(vec_)\
    (free(vector__head(vec_)))


/** Gets the current element count */
#define vector_size(vec_)\
    (vector__head(vec_)[1])


/** Gets the current allocated element count */
#define vector_capacity(vec_)\
    (vector__head(vec_)[0])


/** 1 if vec_ is full, 0 if it's not */
#define vector_full(vec_)\
    (vector_size(vec_) == vector_capacity(vec_))


/** 1 if vec_ is empty, 0 if it's not */
#define vector_empty(vec_)\
    (vector_size(vec_) == 0)


/** Sets every element in vec_ to val_ */
#define vector_fill(vec_, val_)                        \
    (for (size_t i = 0; i < vector_size(vec_); ++i)    \
        (vec_)[i] = (val_);)

/** Runs fn_ on each element in vec_, then resizes it to the default size*/
#define vector_clear(vec_, fn_)                     \
    do {                                            \
        if ((fn_))                                  \
            vector_foreach(vec_, fn_);              \
        vector_size(vec_) = 0;                      \
        vector__resize(&vector__head(vec_),         \
                         _VEC_DEFAULT_SIZE,         \
                         sizeof(*(vec_)));          \
    } while (0)


/** Resizes vec_ so it can hold at least n_ elements.
 * Does nothing if vec_ can already hold n_ elements */
#define vector_reserve(vec_, n_)                                \
    ((n_) > vector_capacity(vec_)                               \
    ? vector__resize(&vector__head(vec_), n_, sizeof(*(vec_))   \
    : (void)0)


/** Scales vec_ so it has exactly the capacity to hold its elements.
 *  Not recommended if more elements will be added to vec_ */
#define vector_fit(vec_)\
    (vector__resize(&vector__head(vec_), vector_size(vec_), sizeof(*(vec_))))


/** Swaps elements vec_[i1_] and vec_[i2_] */
#define vector_swap(vec_, i1_, i2_)                                 \
    do {                                                            \
        memmove(tmp, (vec_) + (i1_), sizeof(*(vec_)));              \
        memmove((vec_) + (i1_), (vec_) + (i2_), sizeof(*(vec_)));   \
        memmove((vec_) + (i2_), tmp, sizeof(*(vec_)));              \
    } while(0)


/** Returns a pointer to the first element of vec_ */
#define vector_begin(vec_)\
    (vec_)

/** Returns a pointer to one past the last element of vec_ */
#define vector_end(vec_)\
    ((vec_) + vector_size(vec_))


/** Returns the last element in vec_ */
#define vector_last(vec_)\
    ((vec_)[vector_size(vec_) - 1])


/** Inserts val_ at the end of vec_ */
#define vector_push(vec_, val_)     \
    (vector__grow(vec_),            \
    (vec_)[vector_size(vec_)++] = (val_))

/** Adds n_ elements to the end of vec_ and returns a pointer to the first one
 *  Example:
 *          int* my_vec = NULL;
 *          vector_init(my_vec);
 *          int* tmp = vector_push_n(my_vec, 3);
 *          tmp[0] = 1;
 *          tmp[1] = 2;
 *          tmp[2] = 3;
*/
#define vector_push_n(vec_, n_) \
    (vector_reserve(vec_, vector_size(vec_) + (n_)),\
    (vec_) + (vector_size(vec_) - (n_)))


/** Removes and returns the last element in vec_ */
#define vector_pop(vec_)        \
    (vector__shrink(vec_),      \
    (vec_)[--vector_size(vec_)])


/** Inserts elem_ into vec_ at index i_ */
#define vector_insert(vec_, i_, elem_)      \
    do {                                    \
        vector__grow(vec_);                 \
        memmove((vec_) + ((i_) + 1),        \
                (vec_) + ((i_) + 0),        \
                vector_size(vec_) - (i_));  \
        (vec_)[i_] = (elem_);               \
    } while (0)


/** Removes an element from vec_ at index i_.
 * Runs fn_ on the element if fn_ is not null */
#define vector_remove(vec_, i_, fn_)            \
    do {                                        \
        vector__shrink(vec_);                  \
        if (fn_)                                \
            fn_((vec_) + (i_));                 \
        memmove((vec_) + ((i_) + 0),            \
                   (vec_) + ((i_) + 1),         \
                   vector_size(vec_) - (i_));   \
    } while (0)


/** Appends the data of vec2_ to vec1_ */
#define vector_cat(vec1_, vec2_)                                    \
    do {                                                            \
        size_t sz = vector_size(vec1_) + vector_size(vec2_);        \
        vector_reserve(vec1_, sz);                                  \
        memcpy(vector_end(vec_1),                                   \
                  vector_begin(vec2_),                              \
                  vector_size(vec2_) * sizeof(*(vec2_)));           \
    } while(0)


/** Copies the contents of vec1_ into vec2_ */
#define vector_copy(vec1_, vec2_)                                       \
    do {                                                                \
        if (!(vec2_))                                                   \
            break;                                                      \
        memcpy(vec2_, vec1_, vector_size(vec1_) * sizeof(*(vec1_)));    \
        vector_size(vec2_) += vector_size(vec1_);                       \
    } while(0)


/** Sorts vec_ with a qsort compatable function,
 *  i.e. int fn_(const void*, const void*) */
#define vector_sort(vec_, fn_)\
    (qsort(vec_, vector_size(vec_), sizeof(*(vec_)), fn_))


/** Runs __VA_ARGS__ for each element in vec_, accessing them with variable i_
 * Example:
 *      int* my_vec = NULL;
 *          ...
 *      vector_foreach(my_vec, i, {
 *          my_vec[i] += 5;
 *          my_vec[i] -= 10;
 *      });
 *
 * Or:
 *      void my_function(int element)
 *      {
 *          [do stuff with element]
 *      }
 *          ...
 *      vector_foreach(my_vec, x, my_function(my_vec[x]));
 */
#define vector_foreach(vec_, i_, ...)                           \
    (for (size_t (i_) = 0; (i_) < vector_size(vec_); ++(i_))    \
        (__VA_ARGS__)                                           \
    )

#endif /* __DATA_VECTOR_H__ */
