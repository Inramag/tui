#include <tui/console.hpp>

#include <windows.h>

Size Console::size{};

static COORD _cursor;

void Console::init() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

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



void Console::update(const std::wstring& buffer) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(console, {0, 0});

    DWORD written;
    WriteConsoleW(
        console,
        buffer.data(),
        static_cast<DWORD>(buffer.size()),
        &written,
        nullptr
    );

    SetConsoleCursorPosition(console, _cursor);
}
void Console::update(const std::vector<std::wstring>& buffer) {
    std::wstring output;
    output.reserve(buffer.size() * buffer[0].size());

    for (size_t i = 0; i < buffer.size(); i++) {
        output += buffer[i];
        if (i + 1 < buffer.size())
            output += L'\n';
    }

    update(output);
}

void Console::showCursor(bool show) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(console, &info);

    info.bVisible = show;
    SetConsoleCursorInfo(console, &info);
}

void Console::setCursor(int x, int y) {
    _cursor = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
}