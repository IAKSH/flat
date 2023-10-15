file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(new_buffer_test ${sources})
target_include_directories(new_buffer_test PRIVATE include)

add_dependencies(new_buffer_test quickgl)
target_link_libraries(new_buffer_test PRIVATE quickgl)