#include <tui/widgets/button.hpp>

Button::Button(std::string t, std::function<void()> c, bool withBrackets = true) : text(std::move(t)), _withBrackets(withBrackets) {
    setCallback(c);
}

void Button::setCallback(std::function<void()> callback) {
    _binds[Key::Enter] = std::move(callback);
}

std::string Button::render() const {
    return _withBrackets ? ("[ " + text + " ]") : text;
}