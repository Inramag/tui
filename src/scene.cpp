#include <tui/scene.hpp>

#include <tui/tui.hpp>

Scene::Scene(std::unordered_map<Key, std::function<void()>> binds, std::function<std::vector<std::wstring>()> render, std::function<void()> update) : _update(std::move(update)) {
    _binds = {
        { Key::Up, [this] { if (_focusIndex > 0) { _focusIndex--; } } },
        { Key::Down, [this] { if (_focusIndex + 1 < static_cast<int>(widgets.size())) { _focusIndex++; } } }
    };
    for (auto& [key, callback] : binds) _binds.insert_or_assign(key, std::move(callback));

    if (render) _render = std::move(render);
}


Scene& Scene::create() {
    return Tui::createScene();
}



void Scene::clear() {
    _focusIndex = 0;
    widgets.clear();
}

int Scene::getFocusIndex() const { return _focusIndex; }


void Scene::binds() {
    if (_update) _update();

    for (auto& [key, callback] : _binds) {
        if (Input::pressed(key)) {
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