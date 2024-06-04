#pragma once
#include "../export.h"
#include "helper.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#if _WIN32 == 1

#include <windows.h>

#elif __linux == 1

#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

typedef struct mouse
{
    Display *display;
    Window root;
} Mouse;

#endif

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
