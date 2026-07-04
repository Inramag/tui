#pragma once

#include <memory>
#include <vector>

#include <tui/input.hpp>
#include <tui/console.hpp>
#include <tui/widget.hpp>

class Scene {
public:
    template <typename T, typename... Args>
    T& add(Args&&... args) {
        auto widget = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *widget;
        widgets.push_back(std::move(widget));
        return ref;
    }
    void binds();
    void render() const;

    static Scene& create();

protected:
    std::vector<std::unique_ptr<Widget>> widgets;
    int findex = 0;
};