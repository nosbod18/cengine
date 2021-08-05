#include "cengine/core/input.h"
#include "cengine/graphics/window.h"
#include "cengine/core/memory.h"
#include "cengine/core/log.h"
#include "cengine/core/base.h" /* UNUSED macro */

#include "GLFW/glfw3.h"

static void input__refresh(input_t* input);

static input_button_t input__get_key(const input_t* input, int key);
static input_button_t input__get_button(const input_t* input, int button);

/* GLFW callbacks */
static void input__on_key(GLFWwindow* window, int key, int scancode, int action, int mods);
static void input__on_button(GLFWwindow* window, int button, int action, int mods);
static void input__on_mouse_move(GLFWwindow* window, double x, double y);
static void input__on_mouse_scroll(GLFWwindow* window, double x, double y);

input_t*
input_create(const window_t* window)
{
    input_t* input = calloc(1, sizeof(*input));

    if (!input) {
        loge("Failed to create input");
        return NULL;
    }

    /* So input can be accessed from the callbacks */
    glfwSetWindowUserPointer(window->window, input);

    glfwSetKeyCallback(window->window, input__on_key);
    glfwSetMouseButtonCallback(window->window, input__on_button);
    glfwSetCursorPosCallback(window->window, input__on_mouse_move);
    glfwSetScrollCallback(window->window, input__on_mouse_scroll);

    return input;
}

void
input_destroy(input_t* input)
{
    if (!input)
        return;

    free(input);
}

void
input_poll_events(input_t* input)
{
    if (!input)
        return;

    input__refresh(input);
    glfwPollEvents();
}

bool
input_key_down(const input_t* input, int key)
{
    return input__get_key(input, key).down;
}

bool
input_key_pressed(const input_t* input, int key)
{
    return input__get_key(input, key).pressed;
}

bool
input_key_released(const input_t* input, int key)
{
    return input__get_key(input, key).released;
}

bool
input_mouse_down(const input_t* input, int button)
{
    return input__get_button(input, button).down;
}

bool
input_mouse_pressed(const input_t* input, int button)
{
    return input__get_button(input, button).pressed;
}

bool
input_mouse_released(const input_t* input, int button)
{
    return input__get_button(input, button).released;
}

float
input_mouse_xpos(const input_t* input)
{
    if (!input)
        return 0.0f;

    return input->mouse.xpos;
}

float
input_mouse_ypos(const input_t* input)
{
    if (!input)
        return 0.0f;

    return input->mouse.ypos;
}

float
input_mouse_xscroll(const input_t* input)
{
    if (!input)
        return 0.0f;

    return input->mouse.xscroll;
}

float
input_mouse_yscroll(const input_t* input)
{
    if (!input)
        return 0.0f;

    return input->mouse.yscroll;
}

bool
input_mouse_is_trapped(const input_t* input)
{
    if (!input)
        return 0;

    return input->mouse.is_trapped;
}

void
input_mouse_set_trapped(input_t* input, bool trapped)
{
    if (!input)
        return;

    input->mouse.is_trapped = trapped;
}

static void
input__refresh(input_t* input)
{
    if (!input)
        return;

    for (int i = 0; i < KEY_LAST; ++i) {
        input->keyboard.keys[i].pressed = 0;
        input->keyboard.keys[i].released = 0;
    }

    for (int i = 0; i < MOUSE_BUTTON_LAST; ++i) {
        input->mouse.buttons[i].pressed = 0;
        input->mouse.buttons[i].released = 0;
    }

    input->mouse.xscroll = 0;
    input->mouse.yscroll = 0;
}

static input_button_t
input__get_key(const input_t* input, int key)
{
    if (!input || key < 0 || key >= KEY_LAST)
        return (input_button_t){0};

    return input->keyboard.keys[key];
}

static input_button_t
input__get_button(const input_t* input, int button)
{
    if (!input || button < 0 || button >= MOUSE_BUTTON_LAST)
        return (input_button_t){0};

    return input->mouse.buttons[button];
}

static void
input__on_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    UNUSED(scancode); UNUSED(mods);

    input_t* input = glfwGetWindowUserPointer(window);

    if (!input)
        return;

    /* Avoid a seg fault if an unknown key is registered */
    if (key == GLFW_KEY_UNKNOWN)
        key = KEY_UNKNOWN;

    logd("Here");

    switch (action) {
        case ACTION_PRESS: {
            input->keyboard.keys[key].pressed = !input->keyboard.keys[key].down;
            input->keyboard.keys[key].down = 1;
        } break;

        case ACTION_RELEASE: {
            input->keyboard.keys[key].released = 1;
            input->keyboard.keys[key].down = 0;
        } break;

        default: {
        } break;
    }
}

static void
input__on_button(GLFWwindow* window, int button, int action, int mods)
{
    UNUSED(mods);

    input_t* input = glfwGetWindowUserPointer(window);

    if (!input)
        return;

    switch (action) {
        case ACTION_PRESS: {
            input->mouse.buttons[button].pressed = !input->mouse.buttons[button].down;
            input->mouse.buttons[button].down = 1;
        } break;

        case ACTION_RELEASE: {
            input->mouse.buttons[button].released = 1;
            input->mouse.buttons[button].down = 0;
        } break;

        default: {
        } break;
    }
}

static void
input__on_mouse_move(GLFWwindow* window, double x, double y)
{
    input_t* input = glfwGetWindowUserPointer(window);

    if (!input)
        return;

    input->mouse.xpos = x;
    input->mouse.ypos = y;
}

static void
input__on_mouse_scroll(GLFWwindow* window, double x, double y)
{
    input_t* input = glfwGetWindowUserPointer(window);

    if (!input)
        return;

    input->mouse.xscroll = x;
    input->mouse.yscroll = y;
}
