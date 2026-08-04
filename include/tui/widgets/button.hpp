#pragma once

#include <tui/widget.hpp>

class Button : public Widget {
public:
    Button(std::string text, std::function<void()> callback, bool withBrackets = true);
    Button(std::wstring text, std::function<void()> callback, bool withBrackets = true);
    ~Button() override = default;

    std::wstring text;
    bool _withBrackets;

    void setCallback(std::function<void()>);

protected:
    std::wstring render() const override;
};