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


private:
    static void update(const std::string& buffer);
    static void update(const std::vector<std::string>& buffer);

    friend class Scene;
};