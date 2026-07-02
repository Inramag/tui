#pragma once

#include <string>

class Scene;

class Widget {
public:
    Widget();
    virtual ~Widget();

    bool enabled = true;

protected:
    virtual std::string render(bool isFocused) const = 0;
    
    friend class Scene;
};