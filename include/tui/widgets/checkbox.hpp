#pragma once

#include <tui/widget.hpp>

class Checkbox : public Widget {
public:
    Checkbox(std::string text, bool value = false);
    virtual ~Checkbox();

    Checkbox& onChange(std::function<void()> act);

    std::string text;
    bool value;

protected:
    std::string render() const override;

private:
    std::function<void()> _act;
};