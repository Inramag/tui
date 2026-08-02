#include <tui/input.hpp>

#include <algorithm>
#include <vector>

HANDLE Input::_input = GetStdHandle(STD_INPUT_HANDLE);

std::vector<Key> Input::_pressed;
std::vector<Key> Input::_down;

static bool contains(const std::vector<Key>& vec, Key key) {
    return std::find(vec.begin(), vec.end(), key) != vec.end();
}

bool Input::pressed(Key key) {
    return contains(_pressed, key);
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
    ReadConsoleInput(_input, events.data(), count, &count);

    for (DWORD i = 0; i < count; ++i) {
        if (events[i].EventType != KEY_EVENT) continue;

        const KEY_EVENT_RECORD& key = events[i].Event.KeyEvent;
        Key k = static_cast<Key>(key.wVirtualKeyCode);
        
        if (!(k == Key::Enter || k == Key::Escape || (k >= Key::Left && k <= Key::Down) || (k >= Key::N0 && k <= Key::N9) || (k >= Key::A && k <= Key::Z) || (k >= Key::F1 && k <= Key::F12))) continue;

        if (key.bKeyDown) {
            if (!contains(_down, k))
                _pressed.push_back(k);

            _down.push_back(k);
        }
        else {
            _down.erase(std::remove(_down.begin(), _down.end(), k), _down.end());
        }
    }
}