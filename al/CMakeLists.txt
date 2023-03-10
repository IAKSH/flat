cmake_minimum_required(VERSION 3.0.0)
project(flat2AudioTest VERSION 0.1.0)

add_library(audio STATIC)
target_compile_features(audio PUBLIC cxx_std_20)
target_sources(audio PRIVATE audio.hpp al_audio.hpp al_audio.cpp wavaudio.hpp wavaudio.cpp)
target_include_directories(audio PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/openal-soft/include
    ${CMAKE_CURRENT_LIST_DIR}/../3rdparty/minimp3
    )
target_link_directories(audio PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../build/3rdparty/openal-soft/)
target_link_libraries(audio PUBLIC OpenAL32)

add_executable(audio_test)
target_compile_features(audio_test PUBLIC cxx_std_20)
target_sources(audio_test PRIVATE test.cpp)
target_link_libraries(audio_test PUBLIC audio)
