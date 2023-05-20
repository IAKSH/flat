cmake_minimum_required(VERSION 3.0.0)
project(flat3 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(vendor)
add_subdirectory(tests)

add_library(flat)
add_dependencies(flat glfw OpenAL spdlog freetype)
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
    ${CMAKE_CURRENT_LIST_DIR}/core/application.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/pipe.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/object.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/sample.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/physics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/physics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/timer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/sound.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/sample.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/pipe.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/music.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/frame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/renable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_listener.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_listener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_scope.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_source.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenAL/openal_source.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_scope.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_shader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_vao.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_fbo.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/OpenGL/opengl_fbo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/ctti.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/rtti.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/keycode.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/disable_copy.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/abstract_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/logger.hpp
    ${CMAKE_CURRENT_LIST_DIR}/misc/logger.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)