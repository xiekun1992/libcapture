#include "listener.h"

struct Listener context;

#if _WIN32 == 1

int keycode_to_scancode(int keycode)
{
    int scancode = MapVirtualKey(keycode, MAPVK_VK_TO_VSC_EX);
    return scancode;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT hookStruct = (PKBDLLHOOKSTRUCT)lParam;
    switch (wParam)
    {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
        long params[7] = {L_KEYDOWN, (long)hookStruct->vkCode, (long)keycode_to_scancode(hookStruct->vkCode)};
        if (hookStruct->vkCode == VK_LCONTROL)
        {
            context.is_lcontrol_down = true;
        }
        if (hookStruct->vkCode == VK_LSHIFT)
        {
            context.is_lshift_down = true;
        }
        if (hookStruct->vkCode == VK_LWIN)
        {
            context.is_lwin_down = true;
        }
        if (hookStruct->vkCode == VK_LMENU)
        {
            context.is_lalt_down = true;
        }
        if (hookStruct->vkCode == VK_ESCAPE)
        {
            context.is_escape_down = true;
        }
        if (context.is_lcontrol_down &&
            context.is_lshift_down &&
            context.is_lwin_down &&
            context.is_lalt_down &&
            context.is_escape_down)
        {
            context.hotkeyHandler();
        }
        context.keyboardHanlder(params);
        break;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
        long params[7] = {L_KEYUP, (long)hookStruct->vkCode, (long)keycode_to_scancode(hookStruct->vkCode)};
        if (hookStruct->vkCode == VK_LCONTROL)
        {
            context.is_lcontrol_down = false;
        }
        if (hookStruct->vkCode == VK_LSHIFT)
        {
            context.is_lshift_down = false;
        }
        if (hookStruct->vkCode == VK_LWIN)
        {
            context.is_lwin_down = false;
        }
        if (hookStruct->vkCode == VK_LMENU)
        {
            context.is_lalt_down = false;
        }
        if (hookStruct->vkCode == VK_ESCAPE)
        {
            context.is_escape_down = false;
        }
        context.keyboardHanlder(params);
        break;
    }
    }
    // printf("%ld %ld %ld\n", wParam, hookStruct->vkCode, hookStruct->scanCode);
    if (context.blocking)
    {
        // Not thses keys: caps lock / scroll lock
        // if (hookStruct->vkCode != VK_CAPITAL && hookStruct->vkCode != VK_SCROLL)
        {
            return 1; // disable key
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // Get event information
    PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
    long mouseData = p->mouseData;
    switch (wParam)
    {
    case WM_MOUSEWHEEL:
    {
        long params[5] = {L_MOUSEWHEEL, (long)p->pt.x, (long)p->pt.y, 0, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_MOUSEMOVE:
    {
        long params[5] = {L_MOUSEMOVE, (long)p->pt.x, (long)p->pt.y, 0, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        long params[5] = {L_MOUSEDOWN, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_LEFT, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_LBUTTONUP:
    {
        long params[5] = {L_MOUSEUP, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_LEFT, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        long params[5] = {L_MOUSEDOWN, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_RIGHT, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_RBUTTONUP:
    {
        long params[5] = {L_MOUSEUP, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_RIGHT, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_MBUTTONDOWN:
    {
        long params[5] = {L_MOUSEDOWN, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_MIDLLE, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    case WM_MBUTTONUP:
    {
        long params[5] = {L_MOUSEUP, (long)p->pt.x, (long)p->pt.y, L_MOUSE_BUTTON_MIDLLE, (long)(mouseData >> 16)};
        context.mouseHanlder(params);
        break;
    }
    }
    if (context.blocking)
    {
        return 1; // disable key
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK deviceHookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_INPUT)
    {
        HRAWINPUT hRawInput = (HRAWINPUT)lParam;
        RAWINPUT input = {0};
        UINT size = sizeof(input);
        GetRawInputData(hRawInput, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));
        // printf("mouse rel move = %ld, %ld\n", input.data.mouse.lLastX, input.data.mouse.lLastY);
        if (MOUSE_MOVE_RELATIVE == input.data.mouse.usFlags)
        {
            // printf("mouse rel %d, move = %ld, %ld\n", input.data.mouse.usFlags, input.data.mouse.lLastX, input.data.mouse.lLastY);
            if (context.blocking)
            {
                long params[5] = {L_MOUSEMOVEREL, input.data.mouse.lLastX, input.data.mouse.lLastY, 0, 0};
                context.mouseHanlder(params);
            }
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

#elif __linux == 1
Display *data_display = NULL;
Display *ctrl_display = NULL;
int stop = 0;

void callback(XPointer pointer, XRecordInterceptData *hook)
{
    static int cursorx, cursory;
    if (hook->category != XRecordFromServer)
    {
        XRecordFreeData(hook);
        return;
    }
    XRecordDatum *data = (XRecordDatum *)hook->data;
    int event_type = data->type;

    BYTE btncode, keycode;
    btncode = keycode = data->event.u.u.detail;
    int rootx = data->event.u.keyButtonPointer.rootX;
    int rooty = data->event.u.keyButtonPointer.rootY;

    switch (event_type)
    {
    case KeyPress:
    {
        long params[3] = {L_KEYDOWN, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(ctrl_display, keycode, 0))), 0};
        lambda_keyboard_handler(params);
        break;
    }
    case KeyRelease:
    {
        long params[3] = {L_KEYUP, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(ctrl_display, keycode, 0))), 0};
        lambda_keyboard_handler(params);
        break;
    }
    case ButtonPress:
        switch (btncode)
        {
        case 1:
        {
            long params[5] = {L_MOUSEDOWN, cursorx, cursory, L_MOUSE_BUTTON_LEFT, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 2:
        {
            long params[5] = {L_MOUSEDOWN, cursorx, cursory, L_MOUSE_BUTTON_MIDLLE, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 3:
        {
            long params[5] = {L_MOUSEDOWN, cursorx, cursory, L_MOUSE_BUTTON_RIGHT, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 4:
        {
            long params[5] = {L_MOUSEWHEEL, cursorx, cursory, 0, -1};
            lambda_mouse_handler(params);
            break; // scroll up
        }
        case 5:
        {
            long params[5] = {L_MOUSEWHEEL, cursorx, cursory, 0, 1};
            lambda_mouse_handler(params);
            break; // scroll down
        }
        }
        break;
    case ButtonRelease:
        switch (btncode)
        {
        case 1:
        {
            long params[5] = {L_MOUSEUP, cursorx, cursory, L_MOUSE_BUTTON_LEFT, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 2:
        {
            long params[5] = {L_MOUSEUP, cursorx, cursory, L_MOUSE_BUTTON_MIDLLE, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 3:
        {
            long params[5] = {L_MOUSEUP, cursorx, cursory, L_MOUSE_BUTTON_RIGHT, 0};
            lambda_mouse_handler(params);
            break;
        }
        case 4:
            break; // scroll up
        case 5:
            break; // scroll down
        }
        break;
    case MotionNotify:
        cursorx = rootx;
        cursory = rooty;
        lambda_mouse_handler(
            new long[5]{L_MOUSEMOVE, cursorx, cursory, 0, 0});
        break;
    }
    XRecordFreeData(hook);
}
#endif

DLL_EXPORT void listener_init(
    void (*mouseHanlder)(long *),
    void (*keyboardHanlder)(long *),
    void (*hotkeyHandler)(void))
{
    context.mouseHanlder = mouseHanlder;
    context.keyboardHanlder = keyboardHanlder;
    context.hotkeyHandler = hotkeyHandler;
    context.is_lcontrol_down = false;
    context.is_lshift_down = false;
    context.is_lwin_down = false;
    context.is_lalt_down = false;
    context.is_escape_down = false;
    context.blocking = false;

#if _WIN32 == 1
    context.mouseHook = SetWindowsHookEx(
        WH_MOUSE_LL,   /* Type of hook */
        mouseHookProc, /* Hook process */
        NULL,          /* Instance */
        0);
    context.keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        keyboardHookProc,
        NULL,
        0);

    WNDCLASSEX wcx = {0};
    wcx.cbSize = sizeof(WNDCLASSEX);
    wcx.lpfnWndProc = deviceHookProc;
    wcx.hInstance = GetModuleHandle(NULL);
    wcx.lpszClassName = TEXT("RawInputClass");
    RegisterClassEx(&wcx);
    HWND hwnd = CreateWindowEx(0, TEXT("RawInputClass"), NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, GetModuleHandle(NULL), NULL);

    RAWINPUTDEVICE rid = {0};
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02; // mouse
    // rid.usUsage = 0x06; // keybaord
    rid.dwFlags = RIDEV_INPUTSINK;
    rid.hwndTarget = hwnd;

    RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE));

#elif __linux == 1
    ctrl_display = XOpenDisplay(NULL);
    data_display = XOpenDisplay(NULL);
    if (!ctrl_display || !data_display)
    {
        // error occur
        exit(1);
    }
    XSynchronize(ctrl_display, true);

    int major, minor;
    if (!XRecordQueryVersion(ctrl_display, &major, &minor))
    {
        exit(2);
    }

    XRecordRange *record_range;
    XRecordClientSpec record_client_spec;
    XRecordContext record_context;
    record_range = XRecordAllocRange();
    if (!record_range)
    {
        exit(3);
    }
    record_range->device_events.first = KeyPress;
    record_range->device_events.last = MotionNotify;
    record_client_spec = XRecordAllClients;
    record_context = XRecordCreateContext(ctrl_display, 0, &record_client_spec, 1, &record_range, 1);
    if (!record_context)
    {
        exit(4);
    }
    if (!XRecordEnableContextAsync(data_display, record_context, callback, NULL))
    {
        exit(5);
    }
    while (true)
    {
        usleep(100); // reduce cpu overhead
        XRecordProcessReplies(data_display);
        if (stop)
        {
            break;
        }
    }
    XRecordDisableContext(ctrl_display, record_context);
    XRecordFreeContext(ctrl_display, record_context);
    XFree(record_range);
    XCloseDisplay(data_display);
    XCloseDisplay(ctrl_display);
#endif
}

DLL_EXPORT void listener_dispose()
{
    // PostQuitMessage(0);
}

DLL_EXPORT void listener_listen()
{
    // https://stackoverflow.com/questions/4509521/does-getmessage-need-a-gui
    // MSG msg;
    // PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    // http://www.winprog.org/tutorial/message_loop.html
    // message loop check, without this, hooks won't work
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        if (Msg.message == WM_QUIT)
        {
            break;
        }
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

DLL_EXPORT void listener_close()
{
#if _WIN32 == 1
    UnhookWindowsHookEx(context.mouseHook);
    UnhookWindowsHookEx(context.keyboardHook);
#elif __linux == 1
    context.blocking = 1;
#endif
}

DLL_EXPORT void listener_setBlock(bool block)
{
    context.blocking = block;
}
