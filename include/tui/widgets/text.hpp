#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>

class Text : public Widget {
public:
    Text(std::string text);
    ~Text() override = default;

    std::string text;

protected:
    std::string render() const override;

private:
    Size pos{};
    int lineCount{};

    Scene* parent{};
    Scene scene;
};