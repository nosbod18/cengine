#ifndef __CORE_INPUT_H__
#define __CORE_INPUT_H__

#include "cengine/graphics/window.h"

#include <stdbool.h>

typedef struct input_button_t
{
    bool down       : 1;
    bool pressed    : 1;
    bool released   : 1;
} input_button_t;

typedef struct input_t
{
    struct {
        input_button_t keys[349];
    } keyboard;

    struct {
        input_button_t buttons[8];
        float xpos,    ypos;
        float xscroll, yscroll;
        bool  is_trapped;
    } mouse;
} input_t;

input_t*    input_create(const window_t* window);
void        input_destroy(input_t* input);

void        input_poll_events(input_t* input);

bool        input_key_down(const input_t* input, int key);
bool        input_key_pressed(const input_t* input, int key);
bool        input_key_released(const input_t* input, int key);

bool        input_mouse_down(const input_t* input, int key);
bool        input_mouse_pressed(const input_t* input, int key);
bool        input_mouse_released(const input_t* input, int key);

float       input_mouse_xpos(const input_t* input);
float       input_mouse_ypos(const input_t* input);
float       input_mouse_xscroll(const input_t* input);
float       input_mouse_yscroll(const input_t* input);

bool        input_mouse_is_trapped(const input_t* input);
void        input_mouse_set_trapped(input_t* input, bool trapped);

enum
{
    KEY_UNKNOWN          = 0,

    /* Printable keys */
    KEY_SPACE            = 32,
    KEY_APOSTROPHE       = 39,  /* ' */
    KEY_COMMA            = 44,  /* , */
    KEY_MINUS            = 45,  /* - */
    KEY_PERIOD           = 46,  /* . */
    KEY_SLASH            = 47,  /* / */
    KEY_0                = 48,
    KEY_1                = 49,
    KEY_2                = 50,
    KEY_3                = 51,
    KEY_4                = 52,
    KEY_5                = 53,
    KEY_6                = 54,
    KEY_7                = 55,
    KEY_8                = 56,
    KEY_9                = 57,
    KEY_SEMICOLON        = 59,  /* ; */
    KEY_EQUAL            = 61,  /* = */
    KEY_A                = 65,
    KEY_B                = 66,
    KEY_C                = 67,
    KEY_D                = 68,
    KEY_E                = 69,
    KEY_F                = 70,
    KEY_G                = 71,
    KEY_H                = 72,
    KEY_I                = 73,
    KEY_J                = 74,
    KEY_K                = 75,
    KEY_L                = 76,
    KEY_M                = 77,
    KEY_N                = 78,
    KEY_O                = 79,
    KEY_P                = 80,
    KEY_Q                = 81,
    KEY_R                = 82,
    KEY_S                = 83,
    KEY_T                = 84,
    KEY_U                = 85,
    KEY_V                = 86,
    KEY_W                = 87,
    KEY_X                = 88,
    KEY_Y                = 89,
    KEY_Z                = 90,
    KEY_LEFT_BRACKET     = 91,  /* [ */
    KEY_BACKSLASH        = 92,  /* \ */
    KEY_RIGHT_BRACKET    = 93,  /* ] */
    KEY_GRAVE_ACCENT     = 96,  /* ` */
    KEY_WORLD_1          = 161, /* non-US #1 */
    KEY_WORLD_2          = 162, /* non-US #2 */

    /* Function keys */
    KEY_ESCAPE           = 256,
    KEY_ENTER            = 257,
    KEY_TAB              = 258,
    KEY_BACKSPACE        = 259,
    KEY_INSERT           = 260,
    KEY_DELETE           = 261,
    KEY_RIGHT            = 262,
    KEY_LEFT             = 263,
    KEY_DOWN             = 264,
    KEY_UP               = 265,
    KEY_PAGE_UP          = 266,
    KEY_PAGE_DOWN        = 267,
    KEY_HOME             = 268,
    KEY_END              = 269,
    KEY_CAPS_LOCK        = 280,
    KEY_SCROLL_LOCK      = 281,
    KEY_NUM_LOCK         = 282,
    KEY_PRINT_SCREEN     = 283,
    KEY_PAUSE            = 284,
    KEY_F1               = 290,
    KEY_F2               = 291,
    KEY_F3               = 292,
    KEY_F4               = 293,
    KEY_F5               = 294,
    KEY_F6               = 295,
    KEY_F7               = 296,
    KEY_F8               = 297,
    KEY_F9               = 298,
    KEY_F10              = 299,
    KEY_F11              = 300,
    KEY_F12              = 301,
    KEY_F13              = 302,
    KEY_F14              = 303,
    KEY_F15              = 304,
    KEY_F16              = 305,
    KEY_F17              = 306,
    KEY_F18              = 307,
    KEY_F19              = 308,
    KEY_F20              = 309,
    KEY_F21              = 310,
    KEY_F22              = 311,
    KEY_F23              = 312,
    KEY_F24              = 313,
    KEY_F25              = 314,
    KEY_KP_0             = 320,
    KEY_KP_1             = 321,
    KEY_KP_2             = 322,
    KEY_KP_3             = 323,
    KEY_KP_4             = 324,
    KEY_KP_5             = 325,
    KEY_KP_6             = 326,
    KEY_KP_7             = 327,
    KEY_KP_8             = 328,
    KEY_KP_9             = 329,
    KEY_KP_DECIMAL       = 330,
    KEY_KP_DIVIDE        = 331,
    KEY_KP_MULTIPLY      = 332,
    KEY_KP_SUBTRACT      = 333,
    KEY_KP_ADD           = 334,
    KEY_KP_ENTER         = 335,
    KEY_KP_EQUAL         = 336,
    KEY_LEFT_SHIFT       = 340,
    KEY_LEFT_CONTROL     = 341,
    KEY_LEFT_ALT         = 342,
    KEY_LEFT_SUPER       = 343,
    KEY_RIGHT_SHIFT      = 344,
    KEY_RIGHT_CONTROL    = 345,
    KEY_RIGHT_ALT        = 346,
    KEY_RIGHT_SUPER      = 347,
    KEY_MENU             = 348,

    KEY_LAST
};

enum
{
    MOUSE_BUTTON_1       = 0,
    MOUSE_BUTTON_2       = 1,
    MOUSE_BUTTON_3       = 2,
    MOUSE_BUTTON_4       = 3,
    MOUSE_BUTTON_5       = 4,
    MOUSE_BUTTON_6       = 5,
    MOUSE_BUTTON_7       = 6,
    MOUSE_BUTTON_8       = 7,

    MOUSE_BUTTON_LAST,

    MOUSE_BUTTON_LEFT    = MOUSE_BUTTON_1,
    MOUSE_BUTTON_RIGHT   = MOUSE_BUTTON_2,
    MOUSE_BUTTON_MIDDLE  = MOUSE_BUTTON_3,
};

enum
{
    MOD_SHIFT            = 0x0001,
    MOD_CONTROL          = 0x0002,
    MOD_ALT              = 0x0004,
    MOD_SUPER            = 0x0008,
    MOD_CAPS_LOCK        = 0x0010,
    MOD_NUM_LOCK         = 0x0020
};

enum
{
    ACTION_PRESS         = 1,
    ACTION_RELEASE       = 2,
    ACTION_REPEAT        = 3
};

#endif /* __CORE_INPUT_H__ */
