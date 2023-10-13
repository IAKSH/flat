file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(fine_light ${sources})
target_include_directories(fine_light PRIVATE include)

add_dependencies(fine_light quickgl)
target_link_libraries(fine_light PRIVATE quickgl)