#include <tui/widgets/textinput.hpp>

#include <tui/tui.hpp>

#include <chrono>

static std::chrono::steady_clock::time_point _lastBackspace;
static bool _repeatBackspace = false;

TextInput::TextInput(std::string _name, std::string _text) : TextInput(toWide(_name), toWide(_text)) {}
TextInput::TextInput(std::string _name, std::wstring _text) : TextInput(toWide(_name), std::move(_text)) {}
TextInput::TextInput(std::wstring _name, std::string _text) : TextInput(std::move(_name), toWide(_text)) {}
TextInput::TextInput(std::wstring _name, std::wstring _text) : name(std::move(_name)), text(std::move(_text)),
    scene({
        { Key::Escape, [this]() {
            Console::showCursor(false);
            Tui::switchScene(parent);
        } },
        { Key::Enter, [this]() {
            text = buff;
            Console::showCursor(false);
            Tui::switchScene(parent);
        } }
    }, [this] {
        Size size = Console::size;
        int center = (size.y - 1) / 2;

        std::vector<std::wstring> buffer(
            center + 1,
            std::wstring(size.x, ' ')
        );

        std::wstring t = buff.substr(std::max(0, (int)buff.length() - size.x));
        buffer[center].replace(0, t.size(), t);

        Console::setCursor(std::min<int>(buff.size(), size.x - 1), center);
        
        return buffer;
    }, [this] {
        wchar_t ch;
        if (Input::pressed(Key::Space)) {
            buff += L' ';
            scene.render();
        }
        for (int i = (int)Key::N0; i < 256; i++) {
            if (Input::pressed(static_cast<Key>(i), ch) && ch >= 32) {
                buff += ch;
                scene.render();
            }
        }
        
        auto now = std::chrono::steady_clock::now();

        auto backspace = [this] {
            if (!buff.empty()) {
                buff.pop_back();
                scene.render();
            }
        };

        if (Input::pressed(Key::Backspace)) {
            backspace();

            _lastBackspace = now;
            _repeatBackspace = false;
        } else if (Input::down(Key::Backspace)) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastBackspace);

            if (!_repeatBackspace) {
                if (elapsed >= std::chrono::milliseconds(400)) {
                    backspace();
                    _lastBackspace = now;
                    _repeatBackspace = true;
                }
            } else {
                if (elapsed >= std::chrono::milliseconds(50)) {
                    backspace();
                    _lastBackspace = now;
                }
            }
        }
    }) {
    _binds[Key::Enter] = [this]() {
        parent = Tui::scene;
        buff = text;
        Tui::switchScene(&scene);
        Console::showCursor(true);
    };
}

std::wstring TextInput::get() const {
    return text;
}

std::wstring TextInput::render() const {
    return name + L": " + text;
}