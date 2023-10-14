#include "utils.h"

DLL_EXPORT void utils_open(wchar_t *path) {
#if _WIN32 == 1
  setlocale(LC_ALL, "");
  SHELLEXECUTEINFO info = { 0 };
  info.cbSize = sizeof(info);
  info.nShow = SW_SHOWDEFAULT;
  info.lpFile = L"explorer.exe";
  info.lpParameters = path;
  ShellExecuteEx(&info);
#elif __linux == 1
#endif
}

DLL_EXPORT void get_screen_size(int size[2]) {
#if _WIN32 == 1
  size[0] = GetSystemMetrics(SM_CXSCREEN);
  size[1] = GetSystemMetrics(SM_CYSCREEN);
#elif __linux == 1
#endif
}