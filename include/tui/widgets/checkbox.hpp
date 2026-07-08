#pragma once

#include <tui/widget.hpp>

class Checkbox : public Widget {
public:
    Checkbox(std::string text, bool value = false);
    ~Checkbox() override = default;

    Checkbox& onChange(std::function<void()> act);

    bool get() const;


protected:
    std::string render() const override;


private:
    std::string text;
    bool value{};

    std::function<void()> _act;
};