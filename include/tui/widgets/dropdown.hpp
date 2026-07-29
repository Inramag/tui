#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>
#include <tui/widgets/button.hpp>

class Dropdown : public Widget {
public:
    Dropdown(std::string text, std::vector<std::string> options);
    ~Dropdown() override = default;

    std::string text;

    std::string curr() const;
    const std::vector<std::string>& options() const;

    void set(std::vector<std::string> options);
    void select(int i);

    void onChange(std::function<void()> act);

protected:
    std::string render() const override;

private:
    int icurr = -1;

    std::vector<std::string> _options;
    std::vector<Button*> _buttons;

    std::function<void()> _onChange;
    
    Scene* _parent{};
    Scene _scene;
};