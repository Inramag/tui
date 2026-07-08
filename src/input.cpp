#include <tui/input.hpp>

#include <vector>

HANDLE Input::_input = GetStdHandle(STD_INPUT_HANDLE);

std::unordered_map<Key, bool> Input::_down;
std::unordered_map<Key, bool> Input::_pressed;

bool Input::isDown(Key key) {
    auto it = _down.find(key);
    return it != _down.end() && it->second;
}
bool Input::isPressed(Key key) {
    auto it = _pressed.find(key);
    return it != _pressed.end() && it->second;
}



void Input::update() {
    _down.clear();

    DWORD count;
    GetNumberOfConsoleInputEvents(_input, &count);

    if (count == 0)
        return;

    std::vector<INPUT_RECORD> events(count);
    ReadConsoleInput(_input, events.data(), count, &count);

    for (DWORD i = 0; i < count; ++i) {
        if (events[i].EventType != KEY_EVENT)
            continue;

        const KEY_EVENT_RECORD& key = events[i].Event.KeyEvent;
        
        switch (key.wVirtualKeyCode) {
            case VK_LEFT:
            case VK_RIGHT:
            case VK_UP:
            case VK_DOWN:
            case VK_RETURN:
            case VK_ESCAPE:
                break;
            default:
                continue;
        }
        Key k = static_cast<Key>(key.wVirtualKeyCode);

        if (key.bKeyDown) {
            if (!_pressed[k])
                _down[k] = true;

            _pressed[k] = true;
        }
        else {
            _pressed[k] = false;
        }
    }
}