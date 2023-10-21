file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_library(quickecs ${sources})
target_include_directories(quickecs PUBLIC include)

add_dependencies(quickecs quickgl)
add_dependencies(quickecs quickal)

target_link_libraries(quickecs PUBLIC quickgl)
target_link_libraries(quickecs PUBLIC quickal)