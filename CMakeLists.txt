cmake_minimum_required(VERSION 3.10)
project(audiotest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.81.0 COMPONENTS system thread)

add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)

add_subdirectory(lib)
add_subdirectory(src)
add_executable(audiotest main.cpp)

target_link_libraries(audiotest PRIVATE ffaudio audio fft ${Boost_LIBRARIES})

target_include_directories(audiotest PUBLIC
                          "."
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffaudio"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffbase"
                          "${PROJECT_SOURCE_DIR}/src/audio"
                          "${PROJECT_SOURCE_DIR}/src/fft"
                          "${PROJECT_SOURCE_DIR}/src/worker"
                           ${Boost_INCLUDE_DIRS}
                          )

message("inc_dirs=${Boost_INCLUDE_DIRS}")
message("lib_dirs=${Boost_LIBRARY_DIRS}")
message("libs=${Boost_LIBRARIES}")
