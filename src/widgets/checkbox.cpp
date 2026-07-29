#include <tui/widgets/checkbox.hpp>

Checkbox::Checkbox(std::string t, bool val) : text(std::move(t)), value(val) {
    _binds[Key::Enter] = [this] { value = !value; if (_onChange) _onChange(); };
}

void Checkbox::onChange(std::function<void()> act) {
    _onChange = std::move(act);
}

std::string Checkbox::render() const {
    std::string ret = "[ ] " + text;
    if (value) ret[1] = 'x';
    return ret;
}