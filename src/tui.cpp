#include <tui/tui.hpp>

#include <deque>

#include <tui/console.hpp>
#include <tui/input.hpp>
#include <tui/scene.hpp>

Scene* Tui::scene = nullptr;
std::deque<Scene> Tui::scenes{};

void Tui::run() {
    Console::size = Console::getSize();
    scene->render();
    while (true) {
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