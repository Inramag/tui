#include <tui/scene.hpp>

#include <tui/tui.hpp>
#include <tui/console.hpp>

void Scene::binds()  {
    bool moved = false;
    if (Input::isDown(Key::Up) && findex > 0) {
        findex--;
        moved = true;
    }
    if (Input::isDown(Key::Down) && findex < static_cast<int>(widgets.size() - 1)) {
        findex++;
        moved = true;
    }
    if (moved) render();
}

void Scene::render() const {
    Size size = Console::GetSize();
    std::vector<std::string> buffer(
        size.y,
        std::string(size.x, ' ')
    );

    int center = (size.y - 1) / 2;

    int start = 0;
    if (findex >= center) start = findex - center;
    int end = std::min(start + size.y - 1, static_cast<int>(widgets.size()-1));

    for (int i = start; i <= end; i++) {
        auto text = widgets[i]->render(i == findex).substr(0, size.x);
        buffer[i - start + std::max(0, center - findex)].replace(0, text.size(), text);
    }
    
    Console::Update(buffer);
}

Scene& Scene::create() {
    return Tui::createScene();
}