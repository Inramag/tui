#pragma once

#include <string>

class Scene;

class Widget {
public:
    Widget();
    virtual ~Widget();

protected:
    virtual std::string render(bool isFocused) const = 0;
    
    friend class Scene;
};