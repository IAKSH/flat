cmake_minimum_required(VERSION 3.0.0)
project(flat3 VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(vendor)
add_subdirectory(demo)

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
    "core/layer.hpp"
    "core/application.hpp"
    "core/application.cpp"
    "core/event_application.hpp"
    "core/event_keyboard.hpp"
    "core/event_mouse.hpp"
    "core/event.hpp"
    "core/mixer.hpp"
    "core/mixer.cpp"
    "core/window.hpp"
    "core/window.cpp"
    "utils/audio.hpp"
    "utils/audio.cpp"
    "utils/logger.hpp"
    "utils/logger.cpp"
    "utils/shader.hpp"
    "utils/shader.cpp"
    "utils/texture.hpp"
    "utils/texture.cpp"
    "utils/timer.hpp"
    "utils/timer.cpp"
    "utils/camera.hpp"
    "utils/camera.cpp"
    "utils/mass_point.hpp"
    "utils/vao.hpp"
    "utils/audio_source.hpp"
    "utils/audio_source.cpp"
    "utils/animation.hpp"
    "utils/font.hpp"
    "utils/font.cpp"
    "utils/wav_dec.hpp"
    "utils/wav_dec.cpp"
    "utils/audio_dec.hpp"
    "utils/any_same.hpp"
    "utils/color.hpp"
    "utils/rectangle_vao.hpp"
    "flat/collision_detect.hpp"
    "flat/gjk.cpp"
    "flat/text_renderer.hpp"
    "flat/text_renderer.cpp"
    "flat/dtype.hpp"
    "flat/shader.hpp"
)

add_executable(flat_test "main.cpp" "demo_obj.hpp" "text.hpp")
add_dependencies(flat_test flat)
target_link_libraries(flat_test flat)
