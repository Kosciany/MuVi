include_directories(".")

add_library(fft FftWorker.cpp FftWorker.h)
target_include_directories(fft PUBLIC
                           "${PROJECT_SOURCE_DIR}/src/worker"
                           )