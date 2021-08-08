#include "engine/graphics/window.h"
#include "engine/core/log.h"
#include "engine/core/memory.h"
#include "engine/core/base.h"

#include "GLFW/glfw3.h"

#include <stdbool.h>

window_t*
window_create(window_props_t* props)
{
    /* --- Init glfw ---------- */
    log_assert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if PLATFORM_APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* native_window = glfwCreateWindow(props->w, props->h, props->title, NULL, NULL);
    log_assert(native_window, "Failed to create native window");

    /* --- Init window ---------- */
    window_t* window = calloc(1, sizeof(*window));
    log_assert(window, "Failed to create window");

    window->window = native_window;
    window->props = *props;

    if (window->props.x == WINDOWPOS_CENTERED
        && window->props.y == WINDOWPOS_CENTERED)
        glfwGetWindowPos(window->window, &window->props.x, &window->props.y);
    else
        glfwSetWindowPos(window->window, window->props.x, window->props.y);

    window->is_maximized = (props->flags >> WINDOW_FULLSCREEN) & 1U;
    window->is_minimized = 0;
    window->is_resizable = !((props->flags >> WINDOW_NOT_RESIZABLE) & 1U);
    window->is_movable   = !((props->flags >> WINDOW_NOT_MOVABLE) & 1U);
    window->is_focused   = 1;
    window->is_vsync     = (props->flags >> WINDOW_VSYNC) & 1U;

    if (window->is_vsync)
        window_set_vsync(window, 1);

    if (window->is_maximized)
        window_maximize(window);

    glfwMakeContextCurrent(window->window);

    return window;
}

void
window_destroy(window_t* window)
{
    if (!window)
        return;

    glfwDestroyWindow(window->window);

    free(window);
    window = NULL;

    glfwTerminate(); /** TODO: For now */
}

void
window_flip(const window_t* window)
{
    if (!window)
        return;

    glfwSwapBuffers(window->window);
}

void
window_set_vsync(window_t* window, bool vsync)
{
    if (!window)
        return;

    window->is_vsync = vsync;
}

bool
window_is_vsync(const window_t* window)
{
    if (!window)
        return 0;

    return window->is_vsync;
}

bool
window_is_open(const window_t* window)
{
    if (!window)
        return 0;

    return !glfwWindowShouldClose(window->window);
}

void
window_maximize(window_t* window)
{
    if (window->is_maximized)
        return;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor)
        return;

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode)
        return;

    glfwGetWindowPos(window->window, &window->props.x, &window->props.y);
    glfwGetWindowSize(window->window, &window->props.w, &window->props.h);
    glfwSetWindowMonitor(window->window,
                         monitor,
                         0,
                         0,
                         mode->width,
                         mode->height,
                         mode->refreshRate);
}

void
window_minimize(window_t* window)
{
    if (!window)
        return;

    window->props.w = 0;
    window->props.h = 0;
    glfwIconifyWindow(window->window);
}

void
window_restore(window_t* window)
{
    if (!window)
        return;

    glfwSetWindowMonitor(window->window,
                         NULL,
                         window->props.x_original,
                         window->props.y_original,
                         window->props.w_original,
                         window->props.h_original,
                         GLFW_DONT_CARE);
}
