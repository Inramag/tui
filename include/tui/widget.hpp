#pragma once

#include <unordered_map>
#include <functional>

#include <string>

#include <tui/input.hpp>

class Scene;

class Widget {
public:
    Widget();
    virtual ~Widget();
    
protected:
    virtual std::string render() const = 0;

    void binds();
    
    friend class Scene;

    std::unordered_map<Key, std::function<void()>> _binds;
};