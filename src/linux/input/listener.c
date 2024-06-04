#include "listener.h"

struct Listener context;

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

DLL_EXPORT void listener_init(
    void (*mouseHanlder)(long *),
    void (*keyboardHanlder)(long *),
    void (*hotkeyHandler)(long[5][7]))
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
}

DLL_EXPORT void listener_dispose()
{
    // PostQuitMessage(0);
}

DLL_EXPORT void listener_listen()
{
}

DLL_EXPORT void listener_close()
{
    context.blocking = 1;
}

DLL_EXPORT void listener_setBlock(bool block)
{
    context.blocking = block;
}
