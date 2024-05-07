#pragma once
#include "export.h"

#include <locale.h>

#if _WIN32 == 1

#include <Windows.h>

#elif __linux == 1

#endif

DLL_EXPORT void utils_open(wchar_t *path);
DLL_EXPORT RECT get_screen_size();
