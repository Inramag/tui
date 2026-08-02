#pragma once

#include <windows.h>

#include <vector>

enum class Key : int {
    Enter = VK_RETURN,
    Escape = VK_ESCAPE,
    Left = VK_LEFT, Up, Right, Down,
    N0 = '0', N1, N2, N3, N4, N5, N6, N7, N8, N9,
    A = 'A', B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    F1 = VK_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

class Input {
public:
    static bool pressed(Key key);
    static bool down(Key key);
    

private:
    static void update();

    friend class Tui;
    

    static HANDLE _input;

    static std::vector<Key> _pressed;
    static std::vector<Key> _down;
};