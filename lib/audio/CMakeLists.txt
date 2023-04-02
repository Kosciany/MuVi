include_directories(".")
IF (WIN32)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-lole32")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffwasapi)
else()
    add_definitions(-DFFAUDIO_INTERFACE_DEFAULT_PTR=&ffalsa)
endif()

add_library(ffaudio ffaudio/wasapi.c ffaudio/audio.h )
target_compile_features(ffaudio PUBLIC cxx_std_11)

