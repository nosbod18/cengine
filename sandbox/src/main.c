#include "cengine/graphics/window.h"
#include "cengine/core/input.h"
#include "cengine/core/memory.h"
#include "cengine/core/log.h"

int
main(void)
{
    window_props_t win_props = {
        "Sandbox",
        WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480,
        WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480,
        0
    };

    window_t* window = window_create(&win_props);
    input_t* input = input_create(window);

    while (window_is_open(window)) {
        input_poll_events(input);

        if (input_key_pressed(input, KEY_A))
            logi("'A' key was pressed this frame");

        window_flip(window);
    }

    input_destroy(input);
    window_destroy(window);
}
