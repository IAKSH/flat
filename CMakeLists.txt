cmake_minimum_required(VERSION 3.0.0)
project(flat2demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(3rdparty/zlib/)
add_subdirectory(3rdparty/glfw/)
add_subdirectory(3rdparty/openal-soft/)

add_executable(flat2demo)
target_compile_features(flat2demo PUBLIC cxx_std_20)
file(GLOB MY_SOURCE_FILES "source/*.cpp" "source/*.hpp" "demo/*.cpp" "demo/*.hpp")
target_sources(flat2demo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/glad/src/glad.c
    ${MY_SOURCE_FILES}
)
target_include_directories(flat2demo PUBLIC 3rdparty/glfw/include)
target_include_directories(flat2demo PUBLIC 3rdparty/glad/include)
target_include_directories(flat2demo PUBLIC 3rdparty/glm)
target_include_directories(flat2demo PUBLIC 3rdparty/openal-soft/include)
target_include_directories(flat2demo PUBLIC 3rdparty/stb-master)
target_include_directories(flat2demo PUBLIC 3rdparty/minimp3)
target_link_directories(flat2demo PUBLIC build/3rdparty/glfw/src)
target_link_directories(flat2demo PUBLIC build/3rdparty/openal-soft)
target_link_libraries(flat2demo PUBLIC glfw3 OpenAL32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
