cmake_minimum_required(VERSION 3.0.0)
project(flat2demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(3rdparty/glfw-3.3.8/)

add_executable(flat2demo)
target_sources(flat2demo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/glad_opengl3.3_core/src/glad.c
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
target_include_directories(flat2demo PUBLIC 3rdparty/glfw-3.3.8/include)
target_include_directories(flat2demo PUBLIC 3rdparty/glad_opengl3.3_core/include)
target_include_directories(flat2demo PUBLIC 3rdparty/glm-0.9.9.8)
target_include_directories(flat2demo PUBLIC 3rdparty/openal-soft-1.23.0-bin/include)
target_include_directories(flat2demo PUBLIC 3rdparty/stb-master)
target_link_directories(flat2demo PUBLIC build/3rdparty/glfw-3.3.8/src)
target_link_libraries(flat2demo PUBLIC glfw3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
