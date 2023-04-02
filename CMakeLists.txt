cmake_minimum_required(VERSION 3.10)
project(audiotest)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)
add_subdirectory(lib)
add_executable(audiotest main.cpp)
target_link_libraries(audiotest PRIVATE audio)
target_include_directories(audiotest PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/audio"
                          )

