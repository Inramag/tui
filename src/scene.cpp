#include <tui/scene.hpp>

#include <tui/console.hpp>
#include <tui/input.hpp>
#include <tui/tui.hpp>

Scene::Scene() : Scene({
        { Key::Up, [this] { if (findex > 0) { findex--; } } },
        { Key::Down, [this] { if (findex < static_cast<int>(widgets.size() - 1)) { findex++; } } }
    }, [this] {
        Size size = Console::getSize();
        std::vector<std::string> buffer(
            size.y,
            std::string(size.x, ' ')
        );

        if (!this->widgets.empty()) {
            int center = (size.y - 1) / 2;

            int start = 0;
            if (findex >= center) start = findex - center;
            int end = std::min(start + size.y - 1, static_cast<int>(widgets.size())-1);

            for (int i = start; i <= end; i++) {
                auto text = widgets[i]->render().substr(0, size.x);
                int bi = i - start + std::max(0, center - findex);
                buffer[bi].replace(0, text.size(), text);
                if (i == findex) buffer[bi] = "\x1b[100m" + buffer[bi] + "\x1b[0m";
            }
        }
        Console::update(buffer);
    }) {}
Scene::Scene(std::unordered_map<Key, std::function<void()>> binds, std::function<void()> render) : _binds(std::move(binds)), _render(std::move(render)) {}

Scene::~Scene() = default;

void Scene::clear() { widgets.clear(); }

int Scene::getFocusIndex() { return findex; }

void Scene::binds()  {
    for (auto& [key, callback] : _binds) {
        if (Input::isDown(key)) {
            callback();
            Tui::scene->render();
        }
    }
    if (widgets.empty())
        return;

    widgets[findex]->binds();
}

void Scene::render() const { if (_render) _render(); }

Scene& Scene::create() { return Tui::createScene(); }