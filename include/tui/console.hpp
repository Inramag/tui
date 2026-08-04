#pragma once

#include <string>
#include <vector>

struct Size {
    int x;
    int y;

    bool operator==(const Size&) const = default;
};

class Console {
public:
    static Size size;

    static void init();
    static Size getSize();

    static void showCursor(bool show);
    static void setCursor(int x, int y);

private:
    static void update(const std::wstring& buffer);
    static void update(const std::vector<std::wstring>& buffer);

    friend class Scene;
};