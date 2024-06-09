#pragma once
#include "../export.h"
#include "scancode.h"

#define KEY_ESC 9
#define KEY_1 10
#define KEY_2 11
#define KEY_3 12
#define KEY_4 13
#define KEY_5 14
#define KEY_6 15
#define KEY_7 16
#define KEY_8 17
#define KEY_9 18
#define KEY_0 19
#define KEY_MINUS 20
#define KEY_EQUAL 21
#define KEY_BACKSPACE 22
#define KEY_TAB 23
#define KEY_Q 24
#define KEY_W 25
#define KEY_E 26
#define KEY_R 27
#define KEY_T 28
#define KEY_Y 29
#define KEY_U 30
#define KEY_I 31
#define KEY_O 32
#define KEY_P 33
#define KEY_LEFTBRACE 34
#define KEY_RIGHTBRACE 35
#define KEY_ENTER 36
#define KEY_LEFTCTRL 37
#define KEY_A 38
#define KEY_S 39
#define KEY_D 40
#define KEY_F 41
#define KEY_G 42
#define KEY_H 43
#define KEY_J 44
#define KEY_K 45
#define KEY_L 46
#define KEY_SEMICOLON 47
#define KEY_APOSTROPHE 48
#define KEY_GRAVE 49
#define KEY_LEFTSHIFT 50
#define KEY_BACKSLASH 51
#define KEY_Z 52
#define KEY_X 53
#define KEY_C 54
#define KEY_V 55
#define KEY_B 56
#define KEY_N 57
#define KEY_M 58
#define KEY_COMMA 59
#define KEY_DOT 60
#define KEY_SLASH 61
#define KEY_RIGHTSHIFT 62
#define KEY_LEFTALT 64
#define KEY_SPACE 65
#define KEY_CAPSLOCK 66
#define KEY_F1 67
#define KEY_F2 68
#define KEY_F3 69
#define KEY_F4 70
#define KEY_F5 71
#define KEY_F6 72
#define KEY_F7 73
#define KEY_F8 74
#define KEY_F9 75
#define KEY_F10 76
#define KEY_F11 95
#define KEY_F12 96
#define KEY_LEFTMETA 133
#define KEY_RIGHTMETA 134
#define KEY_MENU 135
#define KEY_RIGHTCTRL 105
#define KEY_RIGHTALT 108

#define KEY_SYSRQ 107
#define KEY_SCROLLLOCK 78
#define KEY_PAUSE 127
#define KEY_INSERT 118
#define KEY_DELETE 119
#define KEY_HOME 110
#define KEY_END 115
#define KEY_PAGEUP 112
#define KEY_PAGEDOWN 117
#define KEY_UP 111
#define KEY_LEFT 113
#define KEY_RIGHT 114
#define KEY_DOWN 116

// keypads 17
#define KEY_NUMLOCK 77
#define KEY_KPASTERISK 63
#define KEY_KP7 79
#define KEY_KP8 80
#define KEY_KP9 81
#define KEY_KPMINUS 82
#define KEY_KP4 83
#define KEY_KP5 84
#define KEY_KP6 85
#define KEY_KPPLUS 86
#define KEY_KP1 87
#define KEY_KP2 88
#define KEY_KP3 89
#define KEY_KP0 90
#define KEY_KPDOT 91
#define KEY_KPSLASH 106
#define KEY_KPENTER 104

// #define KEY_MUTE 0xe020
// #define KEY_VOLUMEDOWN 0xe02e
// #define KEY_VOLUMEUP 0xe030
// #define KEY_PLAYPAUSE 0xe022
// #define KEY_BACK 0xe010
// #define KEY_FORWARD 0xe019
// #define KEY_STOP
// #define KEY_CALC
// #define KEY_SUSPEND
// #define KEY_CAMERA
// #define KEY_WLAN
// #define KEY_CALC

DLL_EXPORT int scancode_to_keycode(int scancode);
DLL_EXPORT int keycode_to_scancode(int keycode);