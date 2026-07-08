#pragma once

#include <memory>
#include <vector>

#include <tui/input.hpp>
#include <tui/console.hpp>
#include <tui/widget.hpp>

class Scene {
public:
    Scene();
    Scene(std::unordered_map<Key, std::function<void()>>, std::function<void()>);
    ~Scene();

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = default;

    template <typename T, typename... Args>
    T& add(Args&&... args) {
        auto widget = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *widget;
        widgets.push_back(std::move(widget));
        return ref;
    }
    void clear();

    template<class T>
    T& get(size_t i) {
        return static_cast<T&>(*widgets[i]);
    }

    int getFocusIndex();

    void binds();
    void render() const;

    static Scene& create();

private:
    std::unordered_map<Key, std::function<void()>> _binds;
    const std::function<void()> _render;
    
    int findex = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
};