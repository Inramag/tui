#pragma once

#include <unordered_map>
#include <windows.h>

enum class Key : int {
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


private:
    static void update();

    friend class Tui;
    

    static HANDLE _input;
    static std::unordered_map<Key, bool> _down;
    static std::unordered_map<Key, bool> _pressed;
};