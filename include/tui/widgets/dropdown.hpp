#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>
#include <tui/widgets/button.hpp>

class Dropdown : public Widget {
public:
    Dropdown(std::string text, std::vector<std::string> options);
    Dropdown(std::string text, std::vector<std::wstring> options);
    Dropdown(std::wstring text, std::vector<std::string> options);
    Dropdown(std::wstring text, std::vector<std::wstring> options);
    ~Dropdown() override = default;

    std::wstring text;

    std::wstring curr() const;
    const std::vector<std::wstring>& options() const;

    void set(std::vector<std::wstring> options);
    void select(int i);

    void onChange(std::function<void()> act);

protected:
    std::wstring render() const override;

private:
    int icurr = -1;

    std::vector<std::wstring> _options;
    std::vector<Button*> _buttons;

    std::function<void()> _onChange;
    
    Scene* _parent{};
    Scene _scene;
};