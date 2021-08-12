#ifndef CORE_STACK_H
#define CORE_STACK_H

#include "engine/core/vector.h"

#define stack_init(s_)          vector_init(s_)
#define stack_init_with(s_, n_) vector_init_with(s_, n_)
#define stack_free(s_)          vector_free(s_)

#define stack_push(s_, val_)    vector_push(s_, val_)
#define stack_pop(s_)           vector_pop(s_)
#define stack_peek(s_)          vector_last(s_)

#endif /* CORE_STACK_H */
