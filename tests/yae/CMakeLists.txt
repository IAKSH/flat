file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(yae ${sources})
target_include_directories(yae PRIVATE include)

add_dependencies(yae quickgl quickal)
target_link_libraries(yae PRIVATE quickgl quickal)