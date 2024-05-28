#pragma once
#include "export.h"

#include <locale.h>

#if _WIN32 == 1

#include <Windows.h>
#include <shellapi.h>
#include <tchar.h>
#elif __linux == 1

#endif

DLL_EXPORT void utils_open(wchar_t *path);
DLL_EXPORT RECT get_screen_size();
DLL_EXPORT BOOL is_run_as_admin();
DLL_EXPORT VOID run_as_admin();
