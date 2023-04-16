include_directories(".")

add_library(fft FftWorker.cpp FftWorker.h)
target_include_directories(fft PUBLIC
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/audio"
                           "${PROJECT_SOURCE_DIR}/src/worker"
                           "${PROJECT_SOURCE_DIR}/src/logger"
                           ${Boost_INCLUDE_DIRS}
                           )
target_link_libraries(fft PRIVATE spdlog::spdlog)
