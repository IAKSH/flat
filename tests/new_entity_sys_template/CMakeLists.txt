file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(new_entity_sys_template ${sources})
target_include_directories(new_entity_sys_template PRIVATE include)

add_dependencies(new_entity_sys_template quickgl)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(new_entity_sys_template PRIVATE quickgl)
target_link_libraries(new_entity_sys_template PRIVATE imgui::imgui)