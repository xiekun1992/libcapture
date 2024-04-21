#include "keyboard.h"

// struct Keyboard context;

DLL_EXPORT void keyboard_init()
{
#if __linux == 1
  display = XOpenDisplay(NULL);
#elif _WIN32 == 1
#endif
}

void keyboard_dispose()
{
#if __linux == 1
  XCloseDisplay(display);
  // display = NULL;
#elif _WIN32 == 1
#endif
}

int scancode_to_keycode(int scancode)
{
  // VkKeyScanEx(keystr.at(0), context.kbl);
#if __linux == 1
#elif _WIN32 == 1
  int virtualKeyCode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
#endif
  return virtualKeyCode;
}

DLL_EXPORT bool keydown(int *scancodes, int len)
{
#if __linux == 1
  unsigned int keycode = XKeysymToKeycode(display, code);
  XTestFakeKeyEvent(display, keycode, True, 0);
  XFlush(display);
#elif _WIN32 == 1
  INPUT inputs[20] = {0};
  for (int i = 0; i < len; i++)
  {
    if (i > 0)
    {
      break;
    }
    int scancode = scancodes[i];
    int code = scancode_to_keycode(scancode);
    if (code > 0)
    {
      inputs[i].type = INPUT_KEYBOARD;
      inputs[i].ki.wVk = code;
      inputs[i].ki.dwFlags = 0 | KEYEVENTF_EXTENDEDKEY;
      inputs[i].ki.time = 0;
      inputs[i].ki.dwExtraInfo = 0;
      inputs[i].ki.wScan = 0;
    }
  }
  SendInput(20, inputs, sizeof(INPUT));
#endif
  return true;
}

DLL_EXPORT bool keyup(int *scancodes, int len)
{
#if __linux == 1
  unsigned int keycode = XKeysymToKeycode(display, code);
  XTestFakeKeyEvent(display, keycode, False, 0);
  XFlush(display);
#elif _WIN32 == 1
  INPUT inputs[20] = {0};
  for (int i = 0; i < len; i++)
  {
    if (i > 0)
    {
      break;
    }
    int scancode = scancodes[i];
    int code = scancode_to_keycode(scancode);
    if (code > 0)
    {

      inputs[i].type = INPUT_KEYBOARD;
      inputs[i].ki.wVk = code;
      inputs[i].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_EXTENDEDKEY;
      inputs[i].ki.time = 0;
      inputs[i].ki.dwExtraInfo = 0;
      inputs[i].ki.wScan = 0;
    }
  }
  SendInput(20, inputs, sizeof(INPUT));
#endif
  return true;
}
