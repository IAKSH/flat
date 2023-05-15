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
    ${CMAKE_CURRENT_LIST_DIR}/Core/Base/application.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Base/buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Base/filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Base/layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Base/object.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/physics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/physics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_listener.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_listener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_scope.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_source.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenAL/openal_source.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_scope.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_shader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_vao.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/any_same.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/disable_copy.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/logger.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Audio/audio_buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Audio/audio_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Audio/WAV/wav_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Config/config_buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Config/config_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Config/JSON/json_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Image/image_buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Image/image_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Image/Bitmap/bitmap_loadder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceLoadder/Image/PNG/png_loadder.hpp
)

add_executable(flat_test "test.cpp")
add_dependencies(flat_test flat)
target_link_libraries(flat_test flat)
