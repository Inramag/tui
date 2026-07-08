#include <tui/tui.hpp>

#include <deque>

#include <tui/console.hpp>
#include <tui/input.hpp>
#include <tui/scene.hpp>

Scene* Tui::scene = nullptr;
std::deque<Scene> Tui::scenes{};

void Tui::run() {
    DWORD mode;
    GetConsoleMode(Input::_input, &mode);

    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_EXTENDED_FLAGS;
    mode |= ENABLE_WINDOW_INPUT;

    SetConsoleMode(Input::_input, mode);

    Console::size = Console::getSize();
    scene->render();
    while (true) {
        Input::update();
        
        auto newsize = Console::getSize();
        if (Console::size != newsize) {
            Console::size = newsize;
            scene->render();
        }
        scene->binds();
    }
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

void Tui::switchScene(Scene* s) {
    scene = s;
    scene->render();
}