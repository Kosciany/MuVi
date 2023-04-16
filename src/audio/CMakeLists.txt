include_directories(".")
IF (WIN32)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-lole32")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)
else()
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffalsa)
endif()


add_library(audio AudioLoopback.cpp AudioLoopback.h AudioLoopbackWorker.cpp AudioLoopbackWorker.h)
target_include_directories(audio PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffaudio"
                          "${PROJECT_SOURCE_DIR}/lib/audio/ffbase"
                          "${PROJECT_SOURCE_DIR}/src/worker"
                          "${PROJECT_SOURCE_DIR}/src/logger"
                          ${Boost_INCLUDE_DIRS}
                          )
target_link_libraries(audio PRIVATE ffaudio spdlog::spdlog)
target_compile_features(audio PUBLIC cxx_std_11)

