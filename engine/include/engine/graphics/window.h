#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <stdbool.h>

#define WINDOWPOS_CENTERED 0

typedef struct window_props_t
{
    const char* title;
    int x, y;
    int w, h;

    int x_original, y_original;
    int w_original, h_original;

    unsigned int flags;
} window_props_t;

typedef struct window_t
{
    void* window;

    window_props_t props;

    /* Flags */
    bool is_maximized   : 1;
    bool is_minimized   : 1;
    bool is_resizable   : 1;
    bool is_movable     : 1;
    bool is_focused     : 1;
    bool is_vsync       : 1;
} window_t;

enum
{
    WINDOW_VSYNC         = 1U << 0,
    WINDOW_FULLSCREEN    = 1U << 1,
    WINDOW_NOT_RESIZABLE = 1U << 2,
    WINDOW_NOT_MOVABLE   = 1U << 3,
    WINDOW_STATIC        = WINDOW_NOT_RESIZABLE | WINDOW_NOT_MOVABLE,
};

window_t*   window_create(window_props_t* props);
void        window_destroy(window_t* window);

void        window_flip(const window_t* window);

void        window_set_vsync(window_t* window, bool vsync);
bool        window_is_vsync(const window_t* window);

bool        window_is_open(const window_t* window);

void        window_maximize(window_t* window);
void        window_minimize(window_t* window);
void        window_restore(window_t* window);

#endif /* GRAPHICS_WINDOW_H */
