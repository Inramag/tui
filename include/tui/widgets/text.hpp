#pragma once

#include <tui/widget.hpp>

class Text : public Widget {
public:
    Text(const std::string& text);
    virtual ~Text();

    std::string text;

protected:
    std::string render(bool isFocused) const override;
};