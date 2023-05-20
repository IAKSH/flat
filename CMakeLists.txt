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
    ${CMAKE_CURRENT_LIST_DIR}/Core/application.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/pipe.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/sample.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/physics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/physics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/timer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/sound.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/sample.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/pipe.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/music.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/frame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/renable.cpp
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
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_fbo.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/OpenGL/opengl_fbo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Objects/obj_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Objects/obj_camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Objects/obj_drawable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Objects/obj_drawable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/ctti.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/rtti.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/keycode.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/disable_copy.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/abstract_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/logger.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_audio.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_events.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_graphics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_physics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_obj_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_obj_camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_obj_drawable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Misc/Concepts/con_obj_sound.hpp
)

add_executable(flat_test "test.cpp")
add_dependencies(flat_test flat)
target_link_libraries(flat_test flat)
