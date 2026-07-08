#include <tui/widgets/dropdown.hpp>

#include <tui/tui.hpp>

Dropdown::Dropdown(std::string t, std::vector<std::string> variables) : text(std::move(t)) {
    set(variables);
    _binds[Key::Enter] = std::move([this]() {
        if (curr == -1) return;

        this->parent = Tui::scene;
        Tui::switchScene(&scene);
    });
}



std::string Dropdown::get() const {
    if (curr == -1) return "";
    return variables[curr];
}
const std::vector<std::string>& Dropdown::getAll() const {
    return variables;
}

void Dropdown::select(int i) {
    auto str = buttons[curr]->get();
    str[1] = ' ';
    buttons[curr]->set(str);
    
    curr = i;
    
    str = buttons[curr]->get();
    str[1] = '*';
    buttons[curr]->set(str);

    if (parent) Tui::switchScene(parent);
    if (_act) _act();
}

void Dropdown::set(std::vector<std::string> nvariables) {
    variables = std::move(nvariables);
    if (variables.empty()) curr = -1;
    else curr = 0;

    scene.clear();
    buttons.clear();

    if (curr >= 0) {
        for (int i = 0; i < variables.size(); ++i) {
            buttons.push_back(&scene.add<Button>("( ) " + variables[i], [this, i] {
                select(i);
            }));
        }
        select(0);
    }
}

Dropdown& Dropdown::onChange(std::function<void()> act) {
    _act = std::move(act);
    return *this;
}



std::string Dropdown::render() const {
    std::string ret = text + ": ";
    if (curr == -1) ret += "(*)";
    else ret += "[ " + variables[curr] + " ]";
    return ret;
}