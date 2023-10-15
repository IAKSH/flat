file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_executable(dma_buffer_test ${sources})
target_include_directories(dma_buffer_test PRIVATE include)

add_dependencies(dma_buffer_test quickgl)
target_link_libraries(dma_buffer_test PRIVATE quickgl)