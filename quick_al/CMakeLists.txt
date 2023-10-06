file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(quickal ${sources})
target_include_directories(quickal PRIVATE include)