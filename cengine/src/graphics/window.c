#include "cengine/graphics/window.h"
#include "cengine/core/log.h"
#include "cengine/core/memory.h"

#include "GLFW/glfw3.h"

#include <stdbool.h>

ce_Window*
ce_windowCreate(ce_WindowProps* props)
{
    /* --- Init glfw ---------- */
    ce_assert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* nativeWindow = glfwCreateWindow(props->w, props->h, props->title, NULL, NULL);
    ce_assert(nativeWindow, "Failed to create native window");

    /* --- Init window ---------- */
    ce_Window* window = ce_calloc(1, sizeof(*window));
    ce_assert(window, "Failed to create window");

    window->window = nativeWindow;
    window->props = *props;

    if (window->props.x == CE_WINDOWPOS_CENTERED
        && window->props.y == CE_WINDOWPOS_CENTERED)
        glfwGetWindowPos(window->window, &window->props.x, &window->props.y);
    else
        glfwSetWindowPos(window->window, window->props.x, window->props.y);

    window->isMaximized = (props->flags >> CE_WINDOW_FULLSCREEN) & 1U;
    window->isMinimized = 0;
    window->isResizable = !((props->flags >> CE_WINDOW_NOT_RESIZABLE) & 1U);
    window->isMovable   = !((props->flags >> CE_WINDOW_NOT_MOVABLE) & 1U);
    window->isFocused   = 1;
    window->isVsync     = (props->flags >> CE_WINDOW_VSYNC) & 1U;

    if (window->isVsync)
        ce_windowSetVsync(window, 1);

    if (window->isMaximized)
        ce_windowMaximize(window);

    glfwMakeContextCurrent(window->window);

    return window;
}

void
ce_windowDestroy(ce_Window* window)
{
    glfwDestroyWindow(window->window);

    ce_free(window);
    window = NULL;

    glfwTerminate(); /** TODO: For now */
}

void
ce_windowSwapBuffers(const ce_Window* window)
{
    if (!window)
        return;

    glfwSwapBuffers(window->window);
}

void
ce_windowSetVsync(ce_Window* window, bool vsync)
{
    if (!window)
        return;

    window->isVsync = vsync;
}

bool
ce_windowIsVsync(const ce_Window* window)
{
    if (!window)
        return 0;

    return window->isVsync;
}

bool
ce_windowIsOpen(const ce_Window* window)
{
    if (!window)
        return 0;

    return !glfwWindowShouldClose(window->window);
}

void
ce_windowMaximize(ce_Window* window)
{
    if (window->isMaximized)
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
ce_windowMinimize(ce_Window* window)
{
    if (!window)
        return;

    window->props.w = 0;
    window->props.h = 0;
    glfwIconifyWindow(window->window);
}

void
ce_windowRestore(ce_Window* window)
{
    if (!window)
        return;

    glfwSetWindowMonitor(window->window,
                         NULL,
                         window->props.originalX,
                         window->props.originalY,
                         window->props.originalW,
                         window->props.originalH,
                         GLFW_DONT_CARE);
}
