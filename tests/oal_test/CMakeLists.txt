file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(oal_test ${sources})
target_include_directories(oal_test PRIVATE include)

add_dependencies(oal_test quickal)
target_link_libraries(oal_test PRIVATE quickal)