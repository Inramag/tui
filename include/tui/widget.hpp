#pragma once

#include <unordered_map>
#include <functional>

#include <string>

#include <tui/input.hpp>

static std::wstring toWide(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}
static std::vector<std::wstring> toWide(const std::vector<std::string>& vec) {
    std::vector<std::wstring> wideVec;
    wideVec.reserve(vec.size());
    for (const auto& str : vec) {
        wideVec.push_back(toWide(str));
    }
    return wideVec;
}

class Scene;

class Widget {
public:
    Widget() = default;
    virtual ~Widget() = default;


protected:
    virtual std::wstring render() const = 0;

    std::unordered_map<Key, std::function<void()>> _binds;


private:
    void binds();
    
    friend class Scene;
};