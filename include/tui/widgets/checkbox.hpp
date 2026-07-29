#pragma once

#include <tui/widget.hpp>

class Checkbox : public Widget {
public:
    Checkbox(std::string text, bool value = false);
    ~Checkbox() override = default;

    std::string text;
    bool value;

    void onChange(std::function<void()> act);

protected:
    std::string render() const override;

private:
    std::function<void()> _onChange;
};