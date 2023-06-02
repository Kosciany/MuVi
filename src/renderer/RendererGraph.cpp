#if defined(_MSC_VER)
 // Make MS math.h define M_PI
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <climits>

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
        cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
        raw_frame = cv::Mat(MAT_HEIGHT, CHUNK_SIZE, CV_8UC1);
        for (int i = 0; i < MAT_HEIGHT; i++) {
            for (int j = 0; j < CHUNK_SIZE; j++) {
                raw_frame.at<uchar>(MAT_HEIGHT-(i+1), j) = 0;
            }
        }
        memset(&amplitude, 0x00, sizeof(amplitude));
        cv::cvtColor(raw_frame, coloured_frame, cv::COLOR_GRAY2BGR);
    }

    void RendererGraph::Render(fft_buff_t& buff) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            amplitude[j] = (((AVERAGE_WINDOW_SIZE-1))*amplitude[j]/AVERAGE_WINDOW_SIZE) + std::abs(buff.amplitude_1[j])/AVERAGE_WINDOW_SIZE;
            for (int i = 0; i < MAT_HEIGHT; i++) {
                raw_frame.at<uchar>(i, j) = \
                     (i > (log2(amplitude[j]) * 33) ? 0 : i);
            }
        }

        cv::equalizeHist(raw_frame, raw_frame);

        cv::cvtColor(raw_frame, coloured_frame, cv::COLOR_GRAY2BGR);
        cv::applyColorMap(coloured_frame, coloured_frame, cv::COLORMAP_TURBO);

        for (int i = 0; i < MAT_HEIGHT; i++) {
            for (int j = 0; j < CHUNK_SIZE; j++) {
                if(raw_frame.at<uchar>(i, j) == 0){
                    coloured_frame.at<cv::Vec3b>(i, j) = {0, 0, 0};
                };
            }
        }


        cv::resize(coloured_frame, coloured_frame, cv::Size(1280, 720), 0, 0, cv::INTER_CUBIC);
        cv::flip(coloured_frame, coloured_frame, 0);
        PlotGraph();
    }

    void RendererGraph::PlotGraph(void)
    {
        cv::imshow(WINDOW_NAME, coloured_frame);
        cv::waitKey(1);
    }

    void RendererGraph::HandleUI(void)
    {
        PlotGraph();
    }

    RendererGraph::~RendererGraph()
    {

    }

};  // namespace Muvi