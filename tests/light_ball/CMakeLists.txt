file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(light_ball ${sources})
target_include_directories(light_ball PRIVATE include)

add_dependencies(light_ball quickgl)
target_link_libraries(light_ball PRIVATE quickgl)