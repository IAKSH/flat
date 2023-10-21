file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(ecs_test ${sources})
target_include_directories(ecs_test PRIVATE include)

add_dependencies(ecs_test quickcore)
target_link_libraries(ecs_test PRIVATE quickcore)