#ifndef _CE_GRAPHICS_WINDOW_H_
#define _CE_GRAPHICS_WINDOW_H_

#include <stdbool.h>

#define CE_WINDOWPOS_CENTERED 0

typedef struct ce_Window ce_Window;
typedef struct ce_WindowProps ce_WindowProps;

enum
{
    CE_WINDOW_VSYNC         = 1U << 0,
    CE_WINDOW_FULLSCREEN    = 1U << 1,
    CE_WINDOW_NOT_RESIZABLE = 1U << 2,
    CE_WINDOW_NOT_MOVABLE   = 1U << 3,
    CE_WINDOW_STATIC        = CE_WINDOW_NOT_RESIZABLE | CE_WINDOW_NOT_MOVABLE,
};

ce_Window*  ce_windowCreate(ce_WindowProps* props);
void        ce_windowDestroy(ce_Window* window);

void        ce_windowSwapBuffers(const ce_Window* window);

void        ce_windowSetVsync(ce_Window* window, bool vsync);
bool        ce_windowIsVsync(const ce_Window* window);
bool        ce_windowIsOpen(const ce_Window* window);

void        ce_windowMaximize(ce_Window* window);
void        ce_windowMinimize(ce_Window* window);
void        ce_windowRestore(ce_Window* window);


struct ce_WindowProps
{
    const char* title;
    int x, y;
    int w, h;

    int originalX, originalY;
    int originalW, originalH;

    unsigned int flags;
};

struct ce_Window
{
    void* window;

    ce_WindowProps props;

    /* Flags */
    bool isMaximized    : 1;
    bool isMinimized    : 1;
    bool isResizable    : 1;
    bool isMovable      : 1;
    bool isFocused      : 1;
    bool isVsync        : 1;
};


#endif /* _CE_GRAPHICS_WINDOW_H_ */
