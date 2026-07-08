#include <tui/widgets/text.hpp>

#include <tui/tui.hpp>
#include <tui/input.hpp>
#include <tui/scene.hpp>

Text::Text(const std::string& text) :
    text(std::move(text)),
    scene({
        { Key::Up, [this] {
            if (pos.y > 0) pos.y--;
        } },
        { Key::Down, [this] {
            if (pos.y < this->lineCount) pos.y++;
        } },
        { Key::Escape, [this] {
            Tui::switchScene(parent);
        } }
    }, [this] {
        Size size = Console::size;
        std::vector<std::string> buffer(
            size.y,
            std::string(size.x, ' ')
        );

        int center = (size.y - 1) / 2;
        
        int c = 0;
        int start = std::max(0, pos.y - center);
        int l = -start;

        this->lineCount = 0;
        for (const auto& ch : this->text) {
            if (l < 0) {
                if (c == size.x || ch == '\n') {
                    c = 0;
                    l++;
                    this->lineCount++;
                    continue;
                }
                c++;
                continue;
            }

            if (c == size.x || ch == '\n') {
                c = 0;
                l++;
                if (std::max(0, center - pos.y) + l == size.y) break;
                this->lineCount++;
                if (ch == '\n') continue;
            }

            buffer[std::max(0, center - pos.y) + l][c] = ch;
            c++;
        }
        buffer[center] = "\x1b[100m" + buffer[center] + "\x1b[0m";

        Console::update(buffer);
    }) {
    _binds[Key::Enter] = std::move([this] {
        if (this->text.length() > Console::getSize().x) {
            parent = Tui::scene;

            Tui::switchScene(&scene);
        }
    });
}
Text::~Text() = default;

const std::string& Text::get() {
    return text;
}
void Text::set(std::string ntext) {
    text = std::move(ntext);
}

std::string Text::render() const {
    std::string buff;
    int i = 0;
    for (const auto& ch : text) {
        if (ch == '\n' || i == Console::size.x) break;
        buff += ch;
        i++;
    }
    return buff;
}