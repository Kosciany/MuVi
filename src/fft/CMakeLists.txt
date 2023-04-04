include_directories(".")

add_library(fft FftWorker.cpp FftWorker.h)
target_include_directories(fft PUBLIC
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/audio"
                           "${PROJECT_SOURCE_DIR}/src/worker"
                           ${Boost_INCLUDE_DIRS}
                           )