#if defined(_MSC_VER)
 // Make MS math.h define M_PI
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <opencv2/opencv.hpp>

#include "Logger.h"
#include "RendererGraph.h"
#include "FFTBuff.h"

namespace Muvi{

    RendererGraph::RendererGraph()
    {
        frame = new cv::Mat(255, CHUNK_SIZE/4, CV_8UC1);
        cv::namedWindow("MuVi", cv::WINDOW_AUTOSIZE);
    }

    void RendererGraph::Render(fft_buff_t& buff) {

        cv::Mat blurred_frame;
        cv::GaussianBlur(*frame, blurred_frame,cv::Size(5, 5), 0);
        cv::cvtColor(blurred_frame, colour_frame, cv::COLOR_GRAY2BGR);
        cv::applyColorMap(colour_frame, colour_frame, cv::COLORMAP_TURBO);
        
        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < CHUNK_SIZE/4; j++) {
                if(frame->at<uchar>(i, j) == 0){
                    colour_frame.at<cv::Vec3b>(i, j) = {0, 0, 0};
                };
            }
        }

        cv::resize(colour_frame, colour_frame, cv::Size(1280, 720), 0, 0, cv::INTER_CUBIC);
        cv::imshow("MuVi", colour_frame);
        cv::waitKey(1);
        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < CHUNK_SIZE/4; j++) {
                frame->at<uchar>(254-i, j) = i > ((std::abs(buff.amplitude_1[j])*255)/buff.max_amplitude) ? 0 : i;
            }
        }
    }

    RendererGraph::~RendererGraph()
    {
        
    }

};  // namespace Muvi