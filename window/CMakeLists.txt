cmake_minimum_required(VERSION 3.0.0)
project(flat2demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(window)
target_compile_features(window PUBLIC cxx_std_20)
target_sources(window PRIVATE window.hpp glfw_window.hpp glfw_window.cpp ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/glad/src/glad.c)
target_include_directories(window PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/glfw/include
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/glad/include
    )
target_link_directories(window PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../build/3rdparty/glfw/src)
target_link_libraries(window PUBLIC glfw3)

add_executable(window_test)
target_compile_features(window_test PRIVATE cxx_std_20)
target_sources(window_test PRIVATE test.cpp)
target_link_libraries(window_test PRIVATE window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)