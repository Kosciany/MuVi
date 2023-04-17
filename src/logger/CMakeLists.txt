include_directories(".")

add_library(logger Logger.cpp Logger.h)
target_link_libraries(logger PRIVATE spdlog::spdlog)
