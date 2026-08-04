#pragma once

#include <memory>
#include <vector>

#include <tui/input.hpp>
#include <tui/console.hpp>
#include <tui/widget.hpp>

class Scene {
public:
    Scene(std::unordered_map<Key, std::function<void()>> binds = {}, std::function<std::vector<std::wstring>()> render = nullptr, std::function<void()> update = nullptr);
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
    
    void render() const;


private:
    void binds();

    friend class Tui;

    std::function<void()> _update;

    std::unordered_map<Key, std::function<void()>> _binds;
    std::function<std::vector<std::wstring>()> _render = [this] {
        Size size = Console::getSize();
        std::vector<std::wstring> buffer(
            size.y,
            std::wstring(size.x, ' ')
        );

        if (!this->widgets.empty()) {
            int center = (size.y - 1) / 2;

            int start = 0;
            if (_focusIndex >= center) start = _focusIndex - center;
            int end = std::min(start + size.y - std::max(0, center - _focusIndex) - 1, static_cast<int>(widgets.size())-1);

            for (int i = start; i <= end; i++) {
                auto text = widgets[i]->render().substr(0, size.x);
                int bi = i - start + std::max(0, center - _focusIndex);
                buffer[bi].replace(0, text.size(), text);
                if (i == _focusIndex) buffer[bi] = L"\x1b[100m" + buffer[bi] + L"\x1b[0m";
            }
        }
        return buffer;
    };
    
    int _focusIndex = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
};