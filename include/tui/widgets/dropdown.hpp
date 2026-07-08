#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>
#include <tui/widgets/button.hpp>

class Dropdown : public Widget {
public:
    Dropdown(std::string text, std::vector<std::string> variables);
    virtual ~Dropdown();

    Dropdown& onChange(std::function<void()> act);

    std::string text;

    std::string get();
    void select(int i);

    const std::vector<std::string>& getAll();
    void set(std::vector<std::string> nvariables);

private:
    Scene* parent;

    int curr;
    std::vector<std::string> variables;
    std::vector<Button*> buttons;

    Scene scene;

    std::function<void()> _act;

    std::string render() const override;
};