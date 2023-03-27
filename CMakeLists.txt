cmake_minimum_required(VERSION 3.0.0)
project(flat3 VERSION 0.1.0)

add_subdirectory(3rdparty/zlib/)
add_subdirectory(3rdparty/glfw/)
add_subdirectory(3rdparty/googletest/)
add_subdirectory(3rdparty/openal-soft/)
add_subdirectory(3rdparty/freetype/)
add_subdirectory(3rdparty/pybind11/)
add_subdirectory(test)

add_subdirectory(demo)
