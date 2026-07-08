#pragma once

#include <windows.h>

enum class Key {
    Left = VK_LEFT,
    Right = VK_RIGHT,
    Up = VK_UP,
    Down = VK_DOWN,
    Enter = VK_RETURN,
    Escape = VK_ESCAPE 
};

class Input {
public:
    static bool isDown(Key key);
    static bool isPressed(Key key);
};