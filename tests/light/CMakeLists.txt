file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(light ${sources})
target_include_directories(light PRIVATE include)

add_dependencies(light quickgl)
target_link_libraries(light PRIVATE quickgl)