#include <tui/widget.hpp>

#include <tui/tui.hpp>

void Widget::binds() {
    for (auto& [key, callback] : _binds) {
        if (Input::pressed(key)) {
            callback();
            Tui::scene->render();
        }
    }
}