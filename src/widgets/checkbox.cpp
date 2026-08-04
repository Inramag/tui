#include <tui/widgets/checkbox.hpp>

Checkbox::Checkbox(std::string t, bool val) : Checkbox(toWide(t), val) {}
Checkbox::Checkbox(std::wstring t, bool val) : text(std::move(t)), value(val) {
    _binds[Key::Enter] = [this] { value = !value; if (_onChange) _onChange(); };
}

void Checkbox::onChange(std::function<void()> act) {
    _onChange = std::move(act);
}

std::wstring Checkbox::render() const {
    std::wstring ret = L"[ ] " + text;
    if (value) ret[1] = L'x';
    return ret;
}