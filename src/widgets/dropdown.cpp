#include <tui/widgets/dropdown.hpp>

#include <tui/tui.hpp>

Dropdown::Dropdown(std::string t, std::vector<std::string> options) : Dropdown(toWide(t), toWide(options)) {}
Dropdown::Dropdown(std::string t, std::vector<std::wstring> options) : Dropdown(toWide(t), std::move(options)) {}
Dropdown::Dropdown(std::wstring t, std::vector<std::string> options) : Dropdown(std::move(t), toWide(options)) {}
Dropdown::Dropdown(std::wstring t, std::vector<std::wstring> options) : text(std::move(t)) {
    set(options);
    _binds[Key::Enter] = std::move([this]() {
        if (icurr == -1) return;

        this->_parent = Tui::scene;
        Tui::switchScene(&_scene);
    });
}

std::wstring Dropdown::curr() const {
    if (icurr == -1) return L"";
    return _options[icurr];
}
const std::vector<std::wstring>& Dropdown::options() const {
    return _options;
}

void Dropdown::set(std::vector<std::wstring> options) {
    _options = std::move(options);
    if (_options.empty()) icurr = -1;
    else icurr = 0;

    _scene.clear();
    _buttons.clear();

    if (icurr >= 0) {
        for (int i = 0; i < _options.size(); ++i) {
            _buttons.push_back(&_scene.add<Button>(L"( ) " + _options[i], [this, i] {
                select(i);
                Tui::switchScene(_parent);
                if (_onChange) _onChange();
            }));
        }
        select(0);
    }
}
void Dropdown::select(int i) {
    if (icurr == -1) return;
    if (i < 0 || i >= _options.size()) return;

    _buttons[icurr]->text[1] = ' ';
    
    icurr = i;
    
    _buttons[icurr]->text[1] = '*';
}

void Dropdown::onChange(std::function<void()> act) {
    _onChange = std::move(act);
}

std::wstring Dropdown::render() const {
    std::wstring ret = text + L": ";
    if (icurr == -1) ret += L"(*)";
    else ret += L"[ " + _options[icurr] + L" ]";
    return ret;
}