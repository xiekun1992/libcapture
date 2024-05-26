#pragma once
#include "../export.h"

#include <stdbool.h>

#if _WIN32 == 1

#define UNICODE
#define SERVICE_NAME L"Lctrl"

#include <windows.h>
#include <tlhelp32.h>

#elif __linux == 1

#endif

DLL_EXPORT int register_service();
DLL_EXPORT VOID delete_service();
DLL_EXPORT VOID create_service();
DLL_EXPORT VOID stop_service();
DLL_EXPORT VOID start_service();
