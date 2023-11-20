file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(new_entity_sys ${sources})
target_include_directories(new_entity_sys PRIVATE include)

add_dependencies(new_entity_sys quickgl)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(new_entity_sys PRIVATE quickgl)
target_link_libraries(new_entity_sys PRIVATE imgui::imgui)
target_link_libraries(new_entity_sys PRIVATE spdlog::spdlog)