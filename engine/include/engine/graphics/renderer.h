#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "engine/graphics/layer.h"

typedef struct renderer_t
{
    layer_t* layer_stack;
} renderer_t;

renderer_t* renderer_create(void);
void        renderer_destroy(renderer_t* renderer);

void        renderer_push_layer(renderer_t* renderer, layer_t* layer);
void        renderer_pop_layer(renderer_t* renderer);


#endif /* GRAPHICS_RENDERER_H */
