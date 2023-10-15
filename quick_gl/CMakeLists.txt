add_subdirectory(vendor)

#find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp include/*.hpp)
add_library(quickgl ${sources})
target_include_directories(quickgl PUBLIC include)

add_dependencies(quickgl glad)

#target_link_libraries(quickgl PUBLIC glad::glad)
target_link_libraries(quickgl PUBLIC glad)
target_link_libraries(quickgl PUBLIC glfw)
target_link_libraries(quickgl PUBLIC glm::glm)
target_link_libraries(quickgl PUBLIC assimp::assimp)