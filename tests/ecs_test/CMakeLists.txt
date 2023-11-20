file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(ecs_test ${sources})
target_include_directories(ecs_test PRIVATE include)

add_dependencies(ecs_test quickgl)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(ecs_test PRIVATE quickgl)
target_link_libraries(ecs_test PRIVATE imgui::imgui)