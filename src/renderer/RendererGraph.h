#pragma once

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "FFTBuff.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace Muvi {
class RendererGraph {
    private:
        cv::Mat *frame;
        cv::Mat colour_frame;
    public:
        RendererGraph();
        ~RendererGraph();
        void Render(fft_buff_t& buff);
};
}   // namespace Muvi