#pragma once

#include <windows.h>

enum class Key {
    Up = VK_UP,
    Down = VK_DOWN,
    Enter = VK_RETURN
};

class Input {
public:
    static bool isDown(Key key);
};