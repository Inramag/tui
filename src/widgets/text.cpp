#include <tui/widgets/text.hpp>

Text::Text(const std::string& text) : text(std::move(text)) {}
Text::~Text() = default;

std::string Text::render(bool isFocused) const {
    std::string ret;
    ret.reserve(text.size() + 2);
    if (isFocused) ret += "> ";
    else ret += "  ";
    ret += text;
    return ret;
}