cmake_minimum_required(VERSION 3.0.0)
project(flat2demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(3rdparty/zlib/)
add_subdirectory(3rdparty/glfw/)
add_subdirectory(3rdparty/openal-soft/)

add_subdirectory(FlatWindow)
add_subdirectory(FlatAudio)
add_subdirectory(FlatCollision)
add_subdirectory(demo)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
