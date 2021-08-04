#include "cengine/core/memory.h"
#include "cengine/graphics/window.h"

#include <unistd.h>

int
main(void)
{
    ce_WindowProps win_props = {
        "Sandbox",
        CE_WINDOWPOS_CENTERED, CE_WINDOWPOS_CENTERED, 640, 480,
        CE_WINDOWPOS_CENTERED, CE_WINDOWPOS_CENTERED, 640, 480,
        0
    };

    ce_Window* window = ce_windowCreate(&win_props);

    while (ce_windowIsOpen(window)) {
        ce_windowSwapBuffers(window);
    }

    ce_windowDestroy(window);
}
