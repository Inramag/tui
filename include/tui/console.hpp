#pragma once

#include <string>
#include <vector>

struct Size {
    int x, y;

    bool operator==(const Size& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Size& other) const {
        return !(*this == other);
    }
};

class Console {
public:
    static void init();
    static Size getSize();
    static void update(const std::vector<std::string>& buffer);
};