file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(outer_glsl ${sources})
target_include_directories(outer_glsl PRIVATE include)

add_dependencies(outer_glsl quickgl)
target_link_libraries(outer_glsl PRIVATE quickgl)