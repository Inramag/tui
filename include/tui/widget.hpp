#pragma once

#include <unordered_map>
#include <functional>

#include <string>

#include <tui/input.hpp>

class Scene;

class Widget {
public:
    Widget() = default;
    virtual ~Widget() = default;


protected:
    virtual std::string render() const = 0;

    std::unordered_map<Key, std::function<void()>> _binds;


private:
    void binds();
    
    friend class Scene;
};