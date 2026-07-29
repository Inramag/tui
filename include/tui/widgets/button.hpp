#pragma once

#include <tui/widget.hpp>

class Button : public Widget {
public:
    Button(std::string text, std::function<void()> callback);
    ~Button() override = default;

    std::string text;
    bool _withBrackets;

    void setCallback(std::function<void()>);

protected:
    std::string render() const override;
};