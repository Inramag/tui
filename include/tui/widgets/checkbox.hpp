#pragma once

#include <tui/widget.hpp>

class Checkbox : public Widget {
public:
    Checkbox(const std::string& text, bool value);
    virtual ~Checkbox();

    std::string text;
    bool value;

protected:
    std::string render() const override;
};