#include <tui/widget.hpp>

#include <tui/input.hpp>

Widget::Widget() = default;
Widget::~Widget() = default;

void Widget::binds() {
    for (auto& [key, callback] : _binds) {
        if (Input::isDown(key)) callback();
    }
}