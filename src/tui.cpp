#include <tui/tui.hpp>

#include <tui/console.hpp>
#include <tui/input.hpp>

Scene* Tui::scene = nullptr;
std::deque<Scene> Tui::scenes{};

bool Tui::_active = true;

void Tui::run() {
    DWORD mode;
    GetConsoleMode(Input::_input, &mode);

    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_EXTENDED_FLAGS;
    mode |= ENABLE_WINDOW_INPUT;

    SetConsoleMode(Input::_input, mode);

    Console::size = Console::getSize();
    scene->render();
    while (_active) {
        Input::update();
        
        auto nsize = Console::getSize();
        if (Console::size != nsize) {
            Console::size = nsize;
            scene->render();
        }
        scene->binds();
    }
}
void Tui::exit() {
    _active = false;
}

Scene& Tui::createScene() {
    scenes.emplace_back();
    Scene& nscene = scenes.back();
    if (scene == nullptr) scene = &nscene;
    return nscene;
}

void Tui::switchScene(int index) {
    if (index >= 0 && index < static_cast<int>(scenes.size()))
        switchScene(&scenes[index]);
}

void Tui::switchScene(Scene* otherScene) {
    scene = otherScene;
    scene->render();
}