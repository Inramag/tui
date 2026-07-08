#pragma once

#include <tui/widget.hpp>
#include <tui/scene.hpp>

class Text : public Widget {
public:
    Text(const std::string& text);
    virtual ~Text();

    Size pos{};

    const std::string& get();
    void set(std::string ntext);

protected:
    std::string render() const override;

private:
    std::string text;
    int lineCount;

    Scene* parent;
    Scene scene;
};