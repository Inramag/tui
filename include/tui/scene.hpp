#pragma once

#include <vector>

#include <tui/console.hpp>
#include <tui/widget.hpp>

class Scene {
public:
    void add(Widget* widget);
    void render() const;

protected:
    std::vector<Widget*> widgets;
    int findex = 0;
};