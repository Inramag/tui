#include <tui/tui.hpp>

#include <deque>

#include <tui/console.hpp>
#include <tui/input.hpp>
#include <tui/scene.hpp>

Scene* Tui::scene = nullptr;
std::deque<Scene> Tui::scenes{};

void Tui::run() {
    auto size = Console::getSize();
    scene->render();
    while (true) {
        auto newsize = Console::getSize();
        if (size != newsize) {
            size = newsize;
            scene->render();
        }
        scene->binds();
    }
}

Scene& Tui::createScene() {
    scenes.push_back(Scene());
    Scene& nscene = scenes.back();
    if (scene == nullptr) scene = &nscene;
    return nscene;
}

void Tui::switchScene(int index) {
    if (index >= 0 && index < static_cast<int>(scenes.size())) {
        scene = &scenes[index];
    }
    scene->render();
}