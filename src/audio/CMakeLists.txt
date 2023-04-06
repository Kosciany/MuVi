include_directories(".")
IF (WIN32)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-lole32")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)
else()
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffalsa)
endif()


add_library(audio AudioLoopback.cpp AudioLoopback.h AudioLoopbackWorker.cpp AudioLoopbackWorker.h AudioBuff.h)
target_include_directories(audio PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/audio"
                          "${PROJECT_SOURCE_DIR}/src/worker"
                          ${Boost_INCLUDE_DIRS}
                          )
target_link_libraries(audio PRIVATE ffaudio)
target_compile_features(audio PUBLIC cxx_std_20)
