#include <tui/widgets/button.hpp>

Button::Button(const std::string& t, std::function<void()> c) : text(std::move(t)) {
    _binds[Key::Enter] = std::move(c);
}
Button::~Button() = default;

std::string Button::render() const {
    return "[ " + text + " ]";
}