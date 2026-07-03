#include <tui/scene.hpp>

#include <tui/console.hpp>

void Scene::add(Widget* widget) {
    widgets.push_back(widget);
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
    int end = std::min(start + size.y, static_cast<int>(widgets.size()));

    for (int i = start; i < end; i++) {
        buffer[i - start + std::max(0, center - findex)] = widgets[i]->render(i == findex).substr(0, size.x);
    }
    
    Console::Update(buffer);
}