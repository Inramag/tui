#pragma once

#include <tui/widget.hpp>

class Button : public Widget {
public:
    Button(std::string text, std::function<void()> callback);
    ~Button() override = default;

    const std::string& get() const;
    void set(std::string text);


protected:
    std::string render() const override;


private:
    std::string text;
};