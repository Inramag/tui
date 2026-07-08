# tui

> A simple C++20 terminal user interface library.

tui is a lightweight library for building terminal user interfaces in modern C++. It provides scenes, widgets, and keyboard navigation with no external dependencies.

---

## Features

- Scene-based architecture
- Keyboard navigation
- Event-driven widgets
- Scrollable text viewer
- Simple and lightweight design
- No external dependencies

---

## Requirements

- C++20
- CMake 3.20+
- Windows (WinAPI)

---

## Installation

### CMake

Copy the `tui` folder into your project's root directory.

Add the following lines to your project's `CMakeLists.txt`:

```cmake
add_subdirectory(Tui)
target_link_libraries(TuiTest PRIVATE Tui)
```

---

## Quick Start

The simplest `main.cpp`:

```cpp
#include <tui/console.hpp>
#include <tui/tui.hpp>
#include <tui/scene.hpp>
#include <tui/widgets/text.hpp>

int main() {
    Console::init();

    Scene& scene = Scene::create();

    scene.add<Text>("Hello, World!");

    Tui::run();
}
```
This example creates a scene, adds a text widget, and starts the main event loop.

Console:


---

## Concepts

### Tui

The static interface used to control the application.

Main functions:

- `run()` - Starts the main event loop.
- `exit()` - Stops the event loop.
- `switchScene(size_t)` - Switches to another scene by index.

---

### Scene

A scene represents a single screen of your application. It contains widgets and handles user interaction.

Create a scene:

```cpp
Scene& menu = Scene::create();
```

Add widgets:

```cpp
menu.add<Text>("Hello");
menu.add<Button>("Exit", [] {
    Tui::exit();
});
```
where T is a class inherited from Widget.

Switch between scenes:

```cpp
Tui::switchScene(1);
```

---

### Widget

Widgets are the building blocks of the user interface. Each widget is responsible for rendering itself and handling user interaction.

The library provides several built-in widgets, including text labels, buttons, checkboxes, and dropdown lists.

---

## Widgets

### Text

Creates a widget that displays text.

```cpp
scene.add<Text>("text");
```

---

### Button

Creates a widget that executes a callback when it is activated.

```cpp
scene.add<Button>("button", [] {
    // ...
});
```

---

### Checkbox

Creates a widget that can be checked or unchecked.

```cpp
scene.add<Checkbox>("Enable feature");
```

---

### Dropdown

Creates a widget that allows selecting an item from a list.

```cpp
scene.add<Dropdown>(
    "Language",
    {"English", "German", "French"}
);
```

---

## Input

Default keyboard controls:
| Key | Action |
|-----|--------|
| ↑ | Previous widget |
| ↓ | Next widget |
| Enter | Activate |
| Esc | Return |

---

## Project Status

- Under active development
- Windows support

---

## License

MIT License.