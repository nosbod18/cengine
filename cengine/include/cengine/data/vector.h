/**
 * vector.h
 *
 * @brief A dynamically allocated array that can be used with a plain pointer of
 *        any type. Access into the vector is just like a normal array.
 *
 * The vector stores 2 elements of meta-data in front of the user pointer, which
 * contain the current allocated count and the current element count.
 *
 * NOTE: These functions all assume the pointers to be valid,
 *  i.e. they have been passed into ce_vectorInit
 *
 * NOTE: Any functions prefixed with ce__ (two underscores) are meant for internal
 * use and should not be called by the user
 *
 *
 * Functions:
 *              ce_vectorInit(vec_)
 *              ce_vectorInitTo(vec_)
 *              ce_vectorFree(vec_)
 *              ce_vectorSize(vec_)
 *              ce_vectorCapacity(vec_)
 *              ce_vectorIsFull(vec_)
 *              ce_vectorEmpty(vec_)
 *              ce_vectorFill(vec_, val_)
 *              ce_vectorClear(vec_, fn_)
 *              ce_vectorSwap(vec_, i1_, i2_)
 *              ce_vectorBegin(vec_)
 *              ce_vectorEnd(vec_)
 *              ce_vectorLast(vec_)
 *              ce_vectorSort(vec_, fn_)
 *              ce_vectorPush(vec_, val_)
 *              ce_vectorPop(vec_)
 *              ce_vectorInsert(vec_, i_, val_)
 *              ce_vectorRemove(vec_, i_)
 *              ce_vectorCat(vec1_, vec2_)
 *              ce_vectorCopy(vec1_, vec2_)
 *              ce_vectorForeach(vec_, i_, ...)
 */

#ifndef _CE_DATA_VECTOR_H_
#define _CE_DATA_VECTOR_H_

#include "cengine/core/memory.h"
#include <stddef.h> /* size_t */

#define ce__VEC_DEFAULT_SIZE 8

/** Initializes or resizes *vec_ptr with n elements of size type_size */
void ce__vectorResize(size_t** vec_ptr, size_t n, size_t type_size);

#define ce__vectorHead(vec_)\
    ((size_t*)(vec_) - 2)

/** Doubles the capacity of a vector if it's full */
#define ce__vectorGrow(vec_)                                                                \
    (ce_vectorSize(vec_) >= ce_vectorCapacity(vec_)                                         \
    ? ce__vectorResize(&ce__vectorHead(vec_), ce_vectorCapacity(vec_) << 1, sizeof(*vec_))  \
    : (void)0)


/** Halves the capacity of a vector if its size is less than 1/4 its capacity */
#define ce__vectorShrink(vec_)                                                              \
    (ce_vectorSize(vec_) <= ce_vectorCapacity(vec_) >> 2                                    \
    ? ce__vectorResize(&ce__vectorHead(vec_), ce_vectorCapacity(vec_) >> 1, sizeof(*vec_))  \
    : (void)0)


/** Initializes a vector vec_ with n_ elements to start */
#define ce_vectorInit(vec_, n_)     \
    ((vec_) = NULL,                 \
    ce__vectorResize(vec_, n_, sizeof(vec_)))


/** Initializes a vector vec_ with n_ elements to start and fills it with val_ */
#define ce_vectorInitTo(vec_, n_, val_) \
    (ce_vectorInit(vec_, n_),           \
    ce_vectorFill(vec_, val_))          \


/** Frees a vector */
#define ce_vectorFree(vec_)         \
    (ce_free((size_t*)(vec_) - 2),  \
    (vec_) = NULL)


/** Gets the current element count */
#define ce_vectorSize(vec_)\
    (ce__vectorHead(vec_)[1])


/** Gets the current allocated element count */
#define ce_vectorCapacity(vec_)\
    (ce__vectorHead(vec_)[0])


/** 1 if vec_ is full, 0 if it's not */
#define ce_vectorIsFull(vec_)\
    (ce_vectorSize(vec_) == ce_vectorCapacity(vec_))


/** 1 if vec_ is empty, 0 if it's not */
#define ce_vectorEmpty(vec_)\
    (ce_vectorSize(vec_) == 0)


/** Sets every element in vec_ to val_ */
#define ce_vectorFill(vec_, val_)                        \
    (for (size_t i = 0; i < ce_vectorSize(vec_); ++i)    \
        (vec_)[i] = (val_);)

/** Runs fn_ on each element in vec_, then resizes it to the default size*/
#define ce_vectorClear(vec_, fn_)                   \
    do {                                            \
        if ((fn_))                                  \
            ce_vectorForeach(vec_, fn_);            \
        ce_vectorSize(vec_) = 0;                    \
        ce__vectorResize((size_t**)&(vec_),         \
                         ce__VEC_DEFAULT_SIZE,      \
                         sizeof(*(vec_)));          \
    } while (0)


/** Swaps elements vec_[i1_] and vec_[i2_] */
#define ce_vectorSwap(vec_, i1_, i2_)           \
    do {                                        \
        void* a_ = (vec_) + (i1_);              \
        void* b_ = (vec_) + (i2_);              \
        void* t_ = NULL;                        \
        ce_memmove(t_, a_, sizeof(*(vec_)));    \
        ce_memmove(a_, b_, sizeof(*(vec_)));    \
        ce_memmove(b_, t_, sizeof(*(vec_)));    \
    } while(0)


/** Returns a pointer to the first element of vec_ */
#define ce_vectorBegin(vec_)\
    (vec_)

/** Returns a pointer to one past the last element of vec_ */
#define ce_vectorEnd(vec_)\
    ((vec_) + ce_vectorSize(vec_))


/** Returns the last element in vec_ */
#define ce_vectorLast(vec_)\
    ((vec_)[ce_vectorSize(vec_) - 1])


/** Sorts vec_ with a qsort compatable function,
 *  i.e. int fn_(const void*, const void*) */
#define ce_vectorSort(vec_, fn_)\
    (qsort(vec_, ce_vectorSize(vec_), sizeof(*(vec_)), fn_))


/** Inserts val_ at the end of vec_ */
#define ce_vectorPush(vec_, val_)   \
    (ce__vectorGrow(vec_),          \
    (vec_)[ce_vectorSize(vec_)++] = (val_))


/** Removes and returns the last element in vec_ */
#define ce_vectorPop(vec_)      \
    (ce__vectorShrink(vec_),    \
    (vec_)[--ce_vectorSize(vec_)])


/** Inserts elem_ into vec_ at index i_ */
#define ce_vectorInsert(vec_, i_, elem_)        \
    do {                                        \
        ce__vectorGrow(vec_);                   \
        ce_memmove((vec_) + ((i_) + 1),         \
                   (vec_) + ((i_) + 0),         \
                   ce_vectorSize(vec_) - (i_)); \
        (vec_)[i_] = (elem_);                   \
    } while (0)


/** Removes an element from vec_ at index i_.
 * Runs fn_ on the element if fn_ is not null */
#define ce_vectorRemove(vec_, i_, fn_)          \
    do {                                        \
        ce__vectorShrink(vec_);                 \
        if (fn_)                                \
            fn_((vec_) + (i_));                 \
        ce_memmove((vec_) + ((i_) + 0),         \
                   (vec_) + ((i_) + 1),         \
                   ce_vectorSize(vec_) - (i_)); \
    } while (0)


/** Appends the data of vec2_ to vec1_ */
#define ce_vectorCat(vec1_, vec2_)                                      \
    do {                                                                \
        size_t sz = ce_vectorSize(vec1_) + ce_vectorSize(vec2_);        \
        ce__vectorResize((size_t**)&(vec_), sz, sizeof(*(vec_)))        \
        ce_memcpy(ce_vectorEnd(vec_1),                                  \
                  ce_vectorBegin(vec2_),                                \
                  ce_vectorSize(vec2_) * sizeof(*(vec2_)));             \
    } while(0)


/** Copies the contents of vec1_ into vec2_ */
#define ce_vectorCopy(vec1_, vec2_)                                         \
    do {                                                                    \
        if (!(vec2_))                                                       \
            break;                                                          \
        ce_memcpy(vec2_, vec1_, ce_vectorSize(vec1_) * sizeof(*(vec1_)));   \
        ce_vectorSize(vec2_) += ce_vectorSize(vec1_);                       \
    } while(0)


/** Runs __VA_ARGS__ for each element in vec_, accessing them with variable i_
 * Example:
 *      int* my_vec = NULL;
 *          ...
 *      ce_vectorForeach(my_vec, i, {
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
 *      ce_vectorForeach(my_vec, x, my_function(my_vec[x]));
 */
#define ce_vectorForeach(vec_, i_, ...)                          \
    (for (size_t (i_) = 0; (i_) < ce_vectorSize(vec_); ++(i_))   \
        (__VA_ARGS__)                                            \
    )

#endif /* _CE_DATA_VECTOR_H_ */
