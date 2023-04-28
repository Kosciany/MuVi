include_directories(".")
SET(GCC_COVERAGE_COMPILE_FLAGS "-lopengl32 -lglfw3 -lgdi32")
add_library(glad glad/gl.c glad/gl.h)
target_compile_features(glad PUBLIC cxx_std_11)

