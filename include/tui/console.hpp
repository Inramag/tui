#pragma once

#include <string>
#include <vector>

struct Size {
    int x, y;
};

class Console {
public:
    static Size GetSize();
    static void Update(const std::vector<std::string>& buffer);
};