#include <tui/input.hpp>

#include <algorithm>
#include <vector>

HANDLE Input::_input = GetStdHandle(STD_INPUT_HANDLE);

std::unordered_map<Key, wchar_t> Input::_pressed;
std::vector<Key> Input::_down;

static bool contains(const std::vector<Key>& vec, Key key) {
    return std::find(vec.begin(), vec.end(), key) != vec.end();
}

bool Input::pressed(Key key) {
    return _pressed.find(key) != _pressed.end();
}
bool Input::pressed(Key key, wchar_t& ch) {
    auto it = _pressed.find(key);
    
    if (it == _pressed.end()) return false;

    ch = it->second;
    return true;
}
bool Input::down(Key key) {
    return contains(_down, key);
}



void Input::update() {
    _pressed.clear();

    DWORD count;
    GetNumberOfConsoleInputEvents(_input, &count);

    if (count == 0)
        return;

    std::vector<INPUT_RECORD> events(count);
    ReadConsoleInputW(_input, events.data(), count, &count);

    for (DWORD i = 0; i < count; ++i) {
        if (events[i].EventType != KEY_EVENT) continue;

        const KEY_EVENT_RECORD& key = events[i].Event.KeyEvent;
        Key k = static_cast<Key>(key.wVirtualKeyCode);

        if (key.bKeyDown) {
            if (!contains(_down, k)) {
                _down.push_back(k);
                _pressed[k] = key.uChar.UnicodeChar;
            }
        }
        else _down.erase(std::remove(_down.begin(), _down.end(), k), _down.end());
    }
}