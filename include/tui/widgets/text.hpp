#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>

class Text : public Widget {
public:
    Text(std::string text);
    Text(std::wstring text);
    ~Text() override = default;

    std::wstring text;

protected:
    std::wstring render() const override;

private:
    Size pos{};
    int lineCount{};

    Scene* parent{};
    Scene scene;
};