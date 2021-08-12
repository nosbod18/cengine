#ifndef CORE_QUEUE_H
#define CORE_QUEUE_H

#include "engine/core/vector.h"

#define queue_init(q_)           vector_init(q_)
#define queue_init_with(q_, n_)  vector_init_with(q_, n_)
#define queue_free(q_)           vector_free(q_)

#define queue_enqueue(q_, val_)  vector_push_front(q_, val_)
#define queue_dequeue(q_)        vector_pop(q_)

#endif /* CORE_QUEUE_H */
