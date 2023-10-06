file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(helloworld ${sources})
target_include_directories(helloworld PRIVATE include)

add_dependencies(helloworld quickgl)
target_link_libraries(helloworld PRIVATE quickgl)