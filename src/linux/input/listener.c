#include "listener.h"

struct Listener listener_context;
int dev_i = 0;
int mouse_x = 0, mouse_y = 0;

void handle_event(struct libevdev *dev)
{
    struct input_event ev;
    // printf("111\n");
    while (libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev) == 0)
    {
        // const char *name = libevdev_event_type_get_name(ev.type);
        // const char *code_name = libevdev_event_code_get_name(ev.type, ev.code);
        // printf("Event: %s %d %s %d %d\n", name, ev.type, code_name, ev.code, ev.value);
        // continue;
        if (ev.type == EV_SYN && ev.code == SYN_REPORT)
        {
            while (listener_context.stack_top >= 0)
            {
                struct input_event *ev_frame = &listener_context.ev_stack[listener_context.stack_top];
                if (ev_frame->type == EV_ABS && (ev_frame->code == ABS_X || ev_frame->code == ABS_Y))
                {
                    const char *name = libevdev_event_type_get_name(ev_frame->type);
                    const char *code_name = libevdev_event_code_get_name(ev_frame->type, ev_frame->code);
                    printf("Event: %s %d %s %d %d\n", name, ev_frame->type, code_name, ev_frame->code, ev_frame->value);
                }
                else if (ev_frame->type == EV_REL && REL_X <= ev_frame->code && ev_frame->code <= REL_MISC)
                {
                    const char *name = libevdev_event_type_get_name(ev_frame->type);
                    const char *code_name = libevdev_event_code_get_name(ev_frame->type, ev_frame->code);
                    printf("Event: %s %d %s %d %d\n", name, ev_frame->type, code_name, ev_frame->code, ev_frame->value);

                    switch (ev_frame->code)
                    {
                    case REL_WHEEL:
                    {
                        if (ev_frame->value == -1)
                        {
                            long params[5] = {L_MOUSEWHEEL, 0, 0, 0, 1};
                            listener_context.mouseHanlder(params);
                        }
                        if (ev_frame->value == 1)
                        {
                            long params[5] = {L_MOUSEWHEEL, 0, 0, 0, -1};
                            listener_context.mouseHanlder(params);
                        }
                        break;
                    }
                    case REL_X:
                    case REL_Y:
                    {
                        break;
                    }

                    default:
                        break;
                    }
                }
                else if (ev_frame->type == EV_KEY && (KEY_RESERVED <= ev_frame->code && ev_frame->code <= KEY_MICMUTE ||
                                                      ev_frame->code == BTN_LEFT || ev_frame->code == BTN_RIGHT || ev_frame->code == BTN_MIDDLE || ev_frame->code == BTN_EXTRA || ev_frame->code == BTN_SIDE))
                {
                    const char *name = libevdev_event_type_get_name(ev_frame->type);
                    const char *code_name = libevdev_event_code_get_name(ev_frame->type, ev_frame->code);
                    printf("Event: %s %d %s %d %d\n", name, ev_frame->type, code_name, ev_frame->code, ev_frame->value);
                    // keyboard
                    if (ev_frame->value == 1)
                    {
                        if (KEY_RESERVED <= ev_frame->code && ev_frame->code <= KEY_MICMUTE)
                        {
                            long params[3] = {L_KEYDOWN, (long)ev_frame->code, 0};
                            listener_context.keyboardHanlder(params);
                        }
                        else
                        {
                            switch (ev_frame->code)
                            {
                            case BTN_LEFT:
                                long params[5] = {L_MOUSEDOWN, 0, 0, L_MOUSE_BUTTON_LEFT, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            case BTN_MIDDLE:
                                long params[5] = {L_MOUSEDOWN, 0, 0, L_MOUSE_BUTTON_MIDLLE, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            case BTN_RIGHT:
                                long params[5] = {L_MOUSEDOWN, 0, 0, L_MOUSE_BUTTON_RIGHT, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    if (ev_frame->value == 0)
                    {
                        if (KEY_RESERVED <= ev_frame->code && ev_frame->code <= KEY_MICMUTE)
                        {
                            long params[3] = {L_KEYUP, (long)ev_frame->code, 0};
                            listener_context.keyboardHanlder(params);
                        }
                        else
                        {
                            switch (ev_frame->code)
                            {
                            case BTN_LEFT:
                                long params[5] = {L_MOUSEUP, 0, 0, L_MOUSE_BUTTON_LEFT, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            case BTN_MIDDLE:
                                long params[5] = {L_MOUSEUP, 0, 0, L_MOUSE_BUTTON_MIDLLE, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            case BTN_RIGHT:
                                long params[5] = {L_MOUSEUP, 0, 0, L_MOUSE_BUTTON_RIGHT, 0};
                                listener_context.mouseHanlder(params);
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
                listener_context.stack_top--;
            }
        }
        else
        {
            listener_context.ev_stack[++listener_context.stack_top] = ev;
        }
    }
}

void list_dir(const char *path)
{
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)))
    {
        // Skip the entries "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // char full_path[1024];
        struct DevNode *node = (struct DevNode *)malloc(sizeof(struct DevNode));
        node->next = NULL;

        snprintf(node->full_path, sizeof(node->full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(node->full_path, &statbuf) == -1)
        {
            perror("stat");
            continue;
        }

        // Check if the entry is a directory
        if (S_ISDIR(statbuf.st_mode))
        {
            // printf("Directory: %s\n", node->full_path);
            // list_dir(node->full_path); // Recursively list subdirectory
        }
        else
        {
            // printf("File: %s\n", node->full_path);
            if (!listener_context.head)
            {
                listener_context.head = node;
                listener_context.tail = node;
            }
            else
            {
                listener_context.tail->next = node;
                listener_context.tail = node;
            }
        }
    }

    closedir(dp);
}

DLL_EXPORT void listener_init(
    void (*mouseHanlder)(long *),
    void (*keyboardHanlder)(long *),
    void (*hotkeyHandler)(long[5][7]))
{
    listener_context.mouseHanlder = mouseHanlder;
    listener_context.keyboardHanlder = keyboardHanlder;
    listener_context.hotkeyHandler = hotkeyHandler;
    listener_context.is_lcontrol_down = false;
    listener_context.is_lshift_down = false;
    listener_context.is_lwin_down = false;
    listener_context.is_lalt_down = false;
    listener_context.is_escape_down = false;
    listener_context.blocking = false;
    listener_context.stack_top = -1;
    listener_context.head = NULL;
    listener_context.tail = NULL;

    list_dir("/dev/input");
    struct DevNode *cur = listener_context.head;

    while (cur)
    {
        const char *f = cur->full_path;
        int fd = open(f, O_RDONLY | O_NONBLOCK);
        if (fd < 0)
        {
            cur = cur->next;
            continue;
        }

        struct libevdev *dev;
        if (libevdev_new_from_fd(fd, &dev) < 0)
        {
            close(fd);
            cur = cur->next;
            continue;
        }

        if (libevdev_get_phys(dev) != NULL && libevdev_has_event_type(dev, EV_KEY) && libevdev_has_event_code(dev, EV_KEY, KEY_A))
        {
            printf("keyboard found: %s\n", f);
            if (libevdev_grab(dev, LIBEVDEV_GRAB) == 0)
            {
                listener_context.fds[dev_i].fd = fd;
                listener_context.fds[dev_i].events = POLLIN;
                listener_context.devs[dev_i] = dev;
                dev_i++;
            }
        }
        if (
            libevdev_get_phys(dev) != NULL &&
            (libevdev_has_event_type(dev, EV_REL) && libevdev_has_event_code(dev, EV_REL, REL_X) ||
             libevdev_has_event_type(dev, EV_ABS) && libevdev_has_event_code(dev, EV_ABS, ABS_X)) &&
            libevdev_has_event_code(dev, EV_KEY, BTN_LEFT))
        {
            printf("mouse found: %s\n", f);
            if (libevdev_grab(dev, LIBEVDEV_GRAB) == 0)
            {
                listener_context.fds[dev_i].fd = fd;
                listener_context.fds[dev_i].events = POLLIN;
                listener_context.devs[dev_i] = dev;
                dev_i++;
            }
        }
        cur = cur->next;
    }
}

DLL_EXPORT void listener_dispose()
{
    for (int i = 0; i < dev_i; i++)
    {
        libevdev_grab(listener_context.devs[i], LIBEVDEV_UNGRAB);
        libevdev_free(listener_context.devs[i]);
        close(listener_context.fds[i].fd);
    }
}

DLL_EXPORT void listener_listen()
{
    // XEvent event;
    // while (1)
    // {
    //     XNextEvent(listener_context.display, &event);
    //     switch (event.type)
    //     {
    //     case KeyPress:
    //     {
    //         long params[3] = {L_KEYDOWN, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(listener_context.display, event.xkey.keycode, 0))), 0};
    //         // long params[3] = {L_KEYDOWN, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(ctrl_display, keycode, 0))), 0};
    //         listener_context.keyboardHanlder(params);
    //         break;
    //     }
    //     case KeyRelease:
    //     {
    //         long params[3] = {L_KEYUP, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(listener_context.display, event.xkey.keycode, 0))), 0};
    //         // long params[3] = {L_KEYUP, (long)XStringToKeysym(XKeysymToString(XKeycodeToKeysym(ctrl_display, keycode, 0))), 0};
    //         listener_context.keyboardHanlder(params);
    //         break;
    //     }
    //     case ButtonPress:
    //         switch (event.xbutton.button)
    //         {
    //         case 1:
    //         {
    //             long params[5] = {L_MOUSEDOWN, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_LEFT, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 2:
    //         {
    //             long params[5] = {L_MOUSEDOWN, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_MIDLLE, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 3:
    //         {
    //             long params[5] = {L_MOUSEDOWN, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_RIGHT, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 4:
    //         {
    //             long params[5] = {L_MOUSEWHEEL, event.xbutton.x, event.xbutton.y, 0, -1};
    //             listener_context.mouseHanlder(params);
    //             break; // scroll up
    //         }
    //         case 5:
    //         {
    //             long params[5] = {L_MOUSEWHEEL, event.xbutton.x, event.xbutton.y, 0, 1};
    //             listener_context.mouseHanlder(params);
    //             break; // scroll down
    //         }
    //         }
    //         break;
    //     case ButtonRelease:
    //         switch (event.xbutton.button)
    //         {
    //         case 1:
    //         {
    //             long params[5] = {L_MOUSEUP, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_LEFT, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 2:
    //         {
    //             long params[5] = {L_MOUSEUP, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_MIDLLE, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 3:
    //         {
    //             long params[5] = {L_MOUSEUP, event.xbutton.x, event.xbutton.y, L_MOUSE_BUTTON_RIGHT, 0};
    //             listener_context.mouseHanlder(params);
    //             break;
    //         }
    //         case 4:
    //             break; // scroll up
    //         case 5:
    //             break; // scroll down
    //         }
    //         break;
    //     case MotionNotify:
    //         long params[5] = {L_MOUSEMOVE, event.xmotion.x, event.xmotion.y, 0, 0};
    //         listener_context.mouseHanlder(params);
    //         break;
    //     }
    //     // if (event.type == MotionNotify)
    //     // {
    //     //     int x = event.xmotion.x;
    //     //     int y = event.xmotion.y;
    //     //     printf("Mouse motion event: x=%d, y=%d\n", x, y);
    //     //     // Limit mouse movement here, for example:
    //     //     if (x != 1 && y != 100)
    //     //     {
    //     //         // Move the mouse to a valid position
    //     //         XWarpPointer(
    //     //             listener_context.display,
    //     //             None,
    //     //             listener_context.root_window,
    //     //             0, 0,
    //     //             0, 0,
    //     //             1, 100);
    //     //     }
    //     // }
    // }
    while (1)
    {
        if (poll(listener_context.fds, dev_i, -1) < 0)
        {
            break;
        }

        for (int i = 0; i < dev_i; i++)
        {
            if (listener_context.fds[i].revents & POLLIN)
            {
                handle_event(listener_context.devs[i]);
            }
        }
    }
}

DLL_EXPORT void listener_close()
{
    // listener_context.blocking = 1;
    // XCloseDisplay(listener_context.display);
}

DLL_EXPORT void listener_setBlock(bool block)
{
    listener_context.blocking = block;
}
