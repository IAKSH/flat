cmake_minimum_required(VERSION 3.0.0)
project(flat3 VERSION 0.1.0)

add_executable(demo_flat)
add_dependencies(demo_flat flat)
target_sources(demo_flat PRIVATE
    "main.cpp"
    "menu.hpp"
    "menu.cpp"
)
target_link_libraries(demo_flat PUBLIC flat)


