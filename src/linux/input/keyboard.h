#pragma once
#include "../export.h"
#include "helper.h"

#include <stdio.h>
#include <stdbool.h>
#if __linux == 1

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#elif _WIN32 == 1

// #define WINVER 0x0500 // SendInput needs this
#include <windows.h>

#endif

// struct Keyboard
// {
// #if __linux == 1
//   Display *display;
// #elif _WIN32 == 1
//   // INPUT ip;
//   // HKL kbl;
// #endif
// };

DLL_EXPORT void keyboard_init();
DLL_EXPORT bool keydown(int *scancodes, int len);
DLL_EXPORT bool keyup(int *scancodes, int len);
void keyboard_dispose();
int scancode_to_keycode(int scancode);
