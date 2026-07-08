#include <tui/widgets/checkbox.hpp>

Checkbox::Checkbox(std::string t, bool val) : text(std::move(t)), value(val) {
    _binds[Key::Enter] = [this] { value = !value; if (_act) _act(); };
}
Checkbox::~Checkbox() = default;



Checkbox& Checkbox::onChange(std::function<void()> act) {
    _act = std::move(act);
    return *this;
}



std::string Checkbox::render() const {
    std::string ret = "[ ] " + text;
    if (value) ret[1] = 'x';
    return ret;
}