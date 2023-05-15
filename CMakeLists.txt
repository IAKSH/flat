cmake_minimum_required(VERSION 3.0.0)
project(flat3 VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(vendor)

add_library(flat)
add_dependencies(flat glfw OpenAL spdlog freetype)
target_compile_features(flat PUBLIC cxx_std_20)
target_link_libraries(flat PUBLIC glfw OpenAL freetype)
target_include_directories(flat PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_LIST_DIR}/vendor/glfw/include
    ${CMAKE_CURRENT_LIST_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_LIST_DIR}/vendor/freetype/include
    ${CMAKE_CURRENT_LIST_DIR}/vendor/glm
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui
    ${CMAKE_CURRENT_LIST_DIR}/vendor/minimp3
    ${CMAKE_CURRENT_LIST_DIR}/vendor/stb
)
target_sources(flat PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/vendor/glad/src/glad.c
    ${CMAKE_CURRENT_LIST_DIR}/vendor/glad/src/glad.c
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
)

add_executable(flat_test "test.cpp")
add_dependencies(flat_test flat)
target_link_libraries(flat_test flat)
