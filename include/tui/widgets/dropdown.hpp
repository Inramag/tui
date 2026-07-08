#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>
#include <tui/widgets/button.hpp>

class Dropdown : public Widget {
public:
    Dropdown(std::string text, std::vector<std::string> variables);
    ~Dropdown() override = default;


    std::string get() const;
    const std::vector<std::string>& getAll() const;

    void select(int i);

    void set(std::vector<std::string> nvariables);

    Dropdown& onChange(std::function<void()> act);


protected:
    std::string render() const override;


private:
    std::string text;
    int curr{-1};

    std::vector<std::string> variables;
    std::vector<Button*> buttons;

    std::function<void()> _act;
    
    Scene* parent{};
    Scene scene;
};