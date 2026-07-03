#include <tui/console.hpp>

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#include <unistd.h>
#endif

Size Console::GetSize() {
    Size size{0, 0};
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#elif defined(__linux__)
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        size.x = w.ws_col;
        size.y = w.ws_row;
    }
#endif
    return size;
}

void Console::Update(const std::vector<std::string>& buffer) {
    std::string output;
    output.reserve(buffer.size() * buffer[0].size());

    for (const auto& line : buffer)
    {
        output += line;
        output += '\n';
    }

#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(console, {0, 0});

    DWORD written;
    WriteConsoleA(
        console,
        output.data(),
        static_cast<DWORD>(output.size()),
        &written,
        nullptr
    );
#elif defined(__linux__)
    std::cout << "\033[H" << output;
#endif
}