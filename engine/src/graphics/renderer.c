#include "engine/graphics/renderer.h"
#include "engine/core/base.h"
#include "engine/core/log.h"
#include "engine/core/memory.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

renderer_t*
renderer_create(void)
{
    renderer_t* renderer = malloc(sizeof(*renderer));

    if (!renderer) {
        loge("Failed to create renderer");
        return NULL;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        loge("Failed to load GLAD");
        return NULL;
    }


    return renderer;
}

void
renderer_destroy(renderer_t* renderer)
{
    free(renderer);
}
