cmake_minimum_required(VERSION 3.20)

project(Tui VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Tui
    src/tui.cpp
    src/input.cpp
    src/console.cpp
    src/scene.cpp
    src/widget.cpp

    src/widgets/text.cpp
)

target_compile_features(Tui PUBLIC cxx_std_20)

target_include_directories(Tui
    PUBLIC
        include
)