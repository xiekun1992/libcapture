#pragma once

#include <stdbool.h>
#if __linux == 1
#elif _WIN32 == 1

// #define WINVER 0x0500 // SendInput needs this
#include <windows.h>

#endif
void switch_to_input_desktop();
