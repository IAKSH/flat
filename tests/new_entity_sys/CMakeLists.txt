file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(new_entity_sys ${sources})
target_include_directories(new_entity_sys PRIVATE include)

add_dependencies(new_entity_sys quickgl)
target_link_libraries(new_entity_sys PRIVATE quickgl)