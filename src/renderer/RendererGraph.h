#pragma once

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "FFTBuff.h"

namespace Muvi {
class RendererGraph {
    private:
        GLFWwindow* window;
        int width, height;
        unsigned int VBO, VAO, EBO;
        unsigned int shaderProgram;
    public:
        RendererGraph();
        ~RendererGraph();
        void Render(fft_buff_t& buff);
};
}   // namespace Muvi