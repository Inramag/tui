#include <tui/widgets/dropdown.hpp>

#include <tui/tui.hpp>

Dropdown::Dropdown(std::string t, std::vector<std::string> options) : text(std::move(t)) {
    set(options);
    _binds[Key::Enter] = std::move([this]() {
        if (icurr == -1) return;

        this->_parent = Tui::scene;
        Tui::switchScene(&_scene);
    });
}

std::string Dropdown::curr() const {
    if (curr == -1) return "";
    return _options[curr];
}
const std::vector<std::string>& Dropdown::options() const {
    return _options;
}

void Dropdown::set(std::vector<std::string> options) {
    _options = std::move(options);
    if (_options.empty()) icurr = -1;
    else icurr = 0;

    _scene.clear();
    _buttons.clear();

    if (icurr >= 0) {
        for (int i = 0; i < _options.size(); ++i) {
            _buttons.push_back(&_scene.add<Button>("( ) " + _options[i], [this, i] {
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

    auto str = _buttons[icurr]->get();
    str[1] = ' ';
    _buttons[icurr]->set(str);
    
    icurr = i;
    
    str = _buttons[icurr]->get();
    str[1] = '*';
    _buttons[icurr]->set(str);
}

void Dropdown::onChange(std::function<void()> act) {
    _onChange = std::move(act);
}

std::string Dropdown::render() const {
    std::string ret = text + ": ";
    if (icurr == -1) ret += "(*)";
    else ret += "[ " + _options[icurr] + " ]";
    return ret;
}