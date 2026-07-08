#include <tui/widgets/button.hpp>

Button::Button(std::string t, std::function<void()> c) : text(std::move(t)) {
    _binds[Key::Enter] = std::move(c);
}



const std::string& Button::get() const {
    return text;
}
void Button::set(std::string text) {
    this->text = std::move(text);
}



std::string Button::render() const {
    return "[ " + text + " ]";
}