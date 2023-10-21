file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_library(quickcore ${sources})
target_include_directories(quickcore PUBLIC include)

add_dependencies(quickcore quickgl)
add_dependencies(quickcore quickal)

target_link_libraries(quickcore PUBLIC quickgl)
target_link_libraries(quickcore PUBLIC quickal)