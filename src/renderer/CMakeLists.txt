include_directories(".")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library(renderer RendererWorker.cpp RendererWorker.h RendererGraph.cpp RendererGraph.h)
target_include_directories(renderer PUBLIC
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/lib/graphics"
                           "${PROJECT_SOURCE_DIR}/src/audio"
                           "${PROJECT_SOURCE_DIR}/src/fft"
                           "${PROJECT_SOURCE_DIR}/src/worker"
                           "${PROJECT_SOURCE_DIR}/src/logger"
                           ${Boost_INCLUDE_DIRS}
                           )

target_link_libraries(renderer PRIVATE spdlog::spdlog ${OpenCV_LIBS})
