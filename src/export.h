#pragma once

#include <stdio.h>
#if _WIN32 == 1

#define UNICODE

#define DLL_EXPORT __declspec(dllexport)

#elif

#endif
