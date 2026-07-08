#include <tui/widgets/checkbox.hpp>

Checkbox::Checkbox(const std::string& t, bool val) : text(std::move(t)), value(val) {
    _binds[Key::Enter] = [this] { value = !value; };
}
Checkbox::~Checkbox() = default;

std::string Checkbox::render() const {
    std::string ret = "[ ] " + text;
    if (value) ret[1] = 'x';
    return ret;
}