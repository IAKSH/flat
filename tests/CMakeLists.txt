cmake_minimum_required(VERSION 3.0.0)
project(pipengine VERSION 0.1.0)

add_executable(flat_test "test.cpp")
add_dependencies(flat_test flat)
target_link_libraries(flat_test flat)

add_test(NAME main COMMAND flat_test)
