file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(new_entity_sys ${sources})
target_include_directories(new_entity_sys PRIVATE include)

add_dependencies(new_entity_sys quickcore)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(new_entity_sys PRIVATE quickcore)
target_link_libraries(new_entity_sys PRIVATE imgui::imgui)