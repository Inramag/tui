#include <tui/input.hpp>

#include <windows.h>

bool Input::isDown(Key key) {
    return GetAsyncKeyState(static_cast<int>(key)) & 0x0001;
}