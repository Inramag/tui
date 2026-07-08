#include <tui/console.hpp>

#include <iostream>

#include <string>
#include <vector>

#include <windows.h>

Size Console::size {};

void Console::init() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(console, &info);

    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
}

Size Console::getSize() {
    Size size{0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return size;
}
void Console::update(const std::string& buffer) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(console, {0, 0});

    DWORD written;
    WriteConsoleA(
        console,
        buffer.data(),
        static_cast<DWORD>(buffer.size()),
        &written,
        nullptr
    );
}
void Console::update(const std::vector<std::string>& buffer) {
    std::string output;
    output.reserve(buffer.size() * buffer[0].size());

    for (size_t i = 0; i < buffer.size(); i++) {
        output += buffer[i];
        if (i + 1 < buffer.size())
            output += '\n';
    }

    update(output);
}