#pragma once
#include "../export.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

struct Mouse
{
    Display *display;
    Window root;
};

enum MouseButton
{
    MOUSE_LEFT = 1,
    MOUSE_MIDDLE,
    MOUSE_RIGHT
};

enum MouseWheel
{
    WHEEL_UP = -1,
    WHEEL_DOWN = 1
};

DLL_EXPORT void mouse_init();
DLL_EXPORT void mouse_dispose();
DLL_EXPORT void mouse_move(int x, int y);
DLL_EXPORT void mouse_wheel(enum MouseWheel direction);
DLL_EXPORT void mouse_down(enum MouseButton button);
DLL_EXPORT void mouse_up(enum MouseButton button);
