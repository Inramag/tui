#pragma once

#include <tui/widget.hpp>

class Checkbox : public Widget {
public:
    Checkbox(std::string text, bool value = false);
    Checkbox(std::wstring text, bool value = false);
    ~Checkbox() override = default;

    std::wstring text;
    bool value;

    void onChange(std::function<void()> act);

protected:
    std::wstring render() const override;

private:
    std::function<void()> _onChange;
};