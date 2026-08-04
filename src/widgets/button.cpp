#include <tui/widgets/button.hpp>

Button::Button(std::string t, std::function<void()> c, bool withBrackets) : Button(toWide(t), c, withBrackets) {}
Button::Button(std::wstring t, std::function<void()> c, bool withBrackets) : text(std::move(t)), _withBrackets(withBrackets) {
    setCallback(c);
}

void Button::setCallback(std::function<void()> callback) {
    _binds[Key::Enter] = std::move(callback);
}

std::wstring Button::render() const {
    return _withBrackets ? (L"[ " + text + L" ]") : text;
}