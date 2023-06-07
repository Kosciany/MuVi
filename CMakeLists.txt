cmake_minimum_required(VERSION 3.10)
project(audiotest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

Include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package( OpenCV REQUIRED )
find_package(Boost 1.81.0 COMPONENTS system thread program_options)

add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)

add_subdirectory(lib)
add_subdirectory(src)
add_executable(audiotest main.cpp)

target_link_libraries(audiotest PRIVATE ffaudio audio fft logger renderer ${Boost_LIBRARIES} spdlog::spdlog ${OpenCV_LIBS})

target_include_directories(audiotest PUBLIC
                          "."
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffaudio"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffbase"
                          "${PROJECT_SOURCE_DIR}/src/audio"
                          "${PROJECT_SOURCE_DIR}/src/fft"
                          "${PROJECT_SOURCE_DIR}/src/worker"
                          "${PROJECT_SOURCE_DIR}/src/logger"
                          "${PROJECT_SOURCE_DIR}/src/renderer"
                           ${Boost_INCLUDE_DIRS}
                           ${OpenCV_INCLUDE_DIRS}
                          )

message("inc_dirs=${Boost_INCLUDE_DIRS}")
message("lib_dirs=${Boost_LIBRARY_DIRS}")
message("libs=${Boost_LIBRARIES}")
