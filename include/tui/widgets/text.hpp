#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>

class Text : public Widget {
public:
    Text(std::string text);
    ~Text() override = default;


    const std::string& get() const;
    void set(std::string ntext);


protected:
    std::string render() const override;


private:
    std::string text;

    Size pos{};
    int lineCount{};

    Scene* parent{};
    Scene scene;
};