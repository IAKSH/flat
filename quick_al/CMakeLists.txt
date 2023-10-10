find_package(OpenAL CONFIG REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_library(quickal ${sources})
target_include_directories(quickal PUBLIC include)

target_link_libraries(quickal PUBLIC OpenAL::OpenAL)