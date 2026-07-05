#include <tui/widgets/dropdown.hpp>

#include <tui/tui.hpp>

Dropdown::Dropdown(const std::string& t, std::vector<std::string> variables) : text(std::move(t)) {
    set(variables);
    _binds[Key::Enter] = std::move([this]() {
        this.parent = Tui::scene;

        if (curr == -1) return;
        Tui::switchScene(&scene);
        scene.render();
    });
}
Dropdown::~Dropdown() = default;

std::string Dropdown::render() const {
    std::string ret = text + ": ";
    if (curr == -1) ret += "(*)";
    else ret += variables[curr];
    return ret;
}

std::string Dropdown::get() {
    if (curr == -1) return "";
    return variables[curr];
}
void Dropdown::select(int i) {
    buttons[curr]->text[1] = ' ';
    curr = i;
    buttons[curr]->text[1] = '*';
    Tui::switchScene(parent);
}

const std::vector<std::string>& Dropdown::getAll() {
    return variables;
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
        buttons[0]->text[1] = '*';
    }
}