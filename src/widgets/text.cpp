#include <tui/widgets/text.hpp>

Text::Text(const std::string& text) : text(std::move(text)) {}
Text::~Text() = default;

std::string Text::render() const {
    return text;
}