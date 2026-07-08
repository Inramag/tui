#pragma once

#include <deque>

#include <tui/scene.hpp>

class Tui {
public:
    static void run();
    static void exit();
    
    static Scene& createScene();
    
    static void switchScene(int index);
    static void switchScene(Scene* scene);

    static Scene* scene; // current scene
    static std::deque<Scene> scenes; // all scenes


private:
    static bool _active;
};