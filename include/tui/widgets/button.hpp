#pragma once

#include <tui/widget.hpp>

class Button : public Widget {
public:
    Button(const std::string& text, std::function<void()> callback);
    virtual ~Button();

    std::string text;

protected:
    std::string render() const override;
};