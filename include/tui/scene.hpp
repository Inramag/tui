#pragma once

#include <memory>
#include <vector>

#include <tui/input.hpp>
#include <tui/console.hpp>
#include <tui/widget.hpp>

class Scene {
public:
    Scene();
    Scene(std::unordered_map<Key, std::function<void()>> binds, std::function<std::vector<std::string>()> render);
    ~Scene() = default;

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = default;


    static Scene& create();


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

    int getFocusIndex() const;


private:
    void binds();
    void render() const;

    friend class Tui;


    std::unordered_map<Key, std::function<void()>> _binds;
    const std::function<std::vector<std::string>()> _render;
    
    int _focusIndex = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
};