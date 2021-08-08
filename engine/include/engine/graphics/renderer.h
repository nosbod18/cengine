#ifndef __GRAPHICS_RENDERER_H__
#define __GRAPHICS_RENDERER_H__


typedef struct renderer_t
{
    int temp;
} renderer_t;

renderer_t* renderer_create(void);
void        renderer_destroy(renderer_t* renderer);


#endif /* __GRAPHICS_RENDERER_H__ */
