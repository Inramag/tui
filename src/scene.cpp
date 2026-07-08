#include <tui/scene.hpp>

#include <tui/tui.hpp>

Scene::Scene() : Scene({
        { Key::Up, [this] { if (_focusIndex > 0) { _focusIndex--; } } },
        { Key::Down, [this] { if (_focusIndex < static_cast<int>(widgets.size() - 1)) { _focusIndex++; } } }
    }, [this] {
        Size size = Console::getSize();
        std::vector<std::string> buffer(
            size.y,
            std::string(size.x, ' ')
        );

        if (!this->widgets.empty()) {
            int center = (size.y - 1) / 2;

            int start = 0;
            if (_focusIndex >= center) start = _focusIndex - center;
            int end = std::min(start + size.y - 1, static_cast<int>(widgets.size())-1);

            for (int i = start; i <= end; i++) {
                auto text = widgets[i]->render().substr(0, size.x);
                int bi = i - start + std::max(0, center - _focusIndex);
                buffer[bi].replace(0, text.size(), text);
                if (i == _focusIndex) buffer[bi] = "\x1b[100m" + buffer[bi] + "\x1b[0m";
            }
        }
        return buffer;
    }) {}
Scene::Scene(std::unordered_map<Key, std::function<void()>> binds, std::function<std::vector<std::string>()> render) : _binds(std::move(binds)), _render(std::move(render)) {}


Scene& Scene::create() {
    return Tui::createScene();
}



void Scene::clear() {
    _focusIndex = 0;
    widgets.clear();
}

int Scene::getFocusIndex() const { return _focusIndex; }


void Scene::binds() {
    for (auto& [key, callback] : _binds) {
        if (Input::isDown(key)) {
            callback();
            Tui::scene->render();
        }
    }
    if (widgets.empty())
        return;

    widgets[_focusIndex]->binds();
}

void Scene::render() const {
    if (_render)
        Console::update(_render());
}