#pragma once
#include "../export.h"
#include "scancode.h"

#define KEYCODE_ESC 9
#define KEYCODE_1 10
#define KEYCODE_2 11
#define KEYCODE_3 12
#define KEYCODE_4 13
#define KEYCODE_5 14
#define KEYCODE_6 15
#define KEYCODE_7 16
#define KEYCODE_8 17
#define KEYCODE_9 18
#define KEYCODE_0 19
#define KEYCODE_MINUS 20
#define KEYCODE_EQUAL 21
#define KEYCODE_BACKSPACE 22
#define KEYCODE_TAB 23
#define KEYCODE_Q 24
#define KEYCODE_W 25
#define KEYCODE_E 26
#define KEYCODE_R 27
#define KEYCODE_T 28
#define KEYCODE_Y 29
#define KEYCODE_U 30
#define KEYCODE_I 31
#define KEYCODE_O 32
#define KEYCODE_P 33
#define KEYCODE_LEFTBRACE 34
#define KEYCODE_RIGHTBRACE 35
#define KEYCODE_ENTER 36
#define KEYCODE_LEFTCTRL 37
#define KEYCODE_A 38
#define KEYCODE_S 39
#define KEYCODE_D 40
#define KEYCODE_F 41
#define KEYCODE_G 42
#define KEYCODE_H 43
#define KEYCODE_J 44
#define KEYCODE_K 45
#define KEYCODE_L 46
#define KEYCODE_SEMICOLON 47
#define KEYCODE_APOSTROPHE 48
#define KEYCODE_GRAVE 49
#define KEYCODE_LEFTSHIFT 50
#define KEYCODE_BACKSLASH 51
#define KEYCODE_Z 52
#define KEYCODE_X 53
#define KEYCODE_C 54
#define KEYCODE_V 55
#define KEYCODE_B 56
#define KEYCODE_N 57
#define KEYCODE_M 58
#define KEYCODE_COMMA 59
#define KEYCODE_DOT 60
#define KEYCODE_SLASH 61
#define KEYCODE_RIGHTSHIFT 62
#define KEYCODE_LEFTALT 64
#define KEYCODE_SPACE 65
#define KEYCODE_CAPSLOCK 66
#define KEYCODE_F1 67
#define KEYCODE_F2 68
#define KEYCODE_F3 69
#define KEYCODE_F4 70
#define KEYCODE_F5 71
#define KEYCODE_F6 72
#define KEYCODE_F7 73
#define KEYCODE_F8 74
#define KEYCODE_F9 75
#define KEYCODE_F10 76
#define KEYCODE_F11 95
#define KEYCODE_F12 96
#define KEYCODE_LEFTMETA 133
#define KEYCODE_RIGHTMETA 134
#define KEYCODE_MENU 135
#define KEYCODE_RIGHTCTRL 105
#define KEYCODE_RIGHTALT 108

#define KEYCODE_SYSRQ 107
#define KEYCODE_SCROLLLOCK 78
#define KEYCODE_PAUSE 127
#define KEYCODE_INSERT 118
#define KEYCODE_DELETE 119
#define KEYCODE_HOME 110
#define KEYCODE_END 115
#define KEYCODE_PAGEUP 112
#define KEYCODE_PAGEDOWN 117
#define KEYCODE_UP 111
#define KEYCODE_LEFT 113
#define KEYCODE_RIGHT 114
#define KEYCODE_DOWN 116

// keypads 17
#define KEYCODE_NUMLOCK 77
#define KEYCODE_KPASTERISK 63
#define KEYCODE_KP7 79
#define KEYCODE_KP8 80
#define KEYCODE_KP9 81
#define KEYCODE_KPMINUS 82
#define KEYCODE_KP4 83
#define KEYCODE_KP5 84
#define KEYCODE_KP6 85
#define KEYCODE_KPPLUS 86
#define KEYCODE_KP1 87
#define KEYCODE_KP2 88
#define KEYCODE_KP3 89
#define KEYCODE_KP0 90
#define KEYCODE_KPDOT 91
#define KEYCODE_KPSLASH 106
#define KEYCODE_KPENTER 104

// #define KEYCODE_MUTE 0xe020
// #define KEYCODE_VOLUMEDOWN 0xe02e
// #define KEYCODE_VOLUMEUP 0xe030
// #define KEYCODE_PLAYPAUSE 0xe022
// #define KEYCODE_BACK 0xe010
// #define KEYCODE_FORWARD 0xe019
// #define KEYCODE_STOP
// #define KEYCODE_CALC
// #define KEYCODE_SUSPEND
// #define KEYCODE_CAMERA
// #define KEYCODE_WLAN
// #define KEYCODE_CALC

DLL_EXPORT int scancode_to_keycode(int scancode);
DLL_EXPORT int keycode_to_scancode(int keycode);