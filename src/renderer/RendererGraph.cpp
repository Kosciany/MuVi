#include "RendererGraph.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <climits>
#include <opencv2/opencv.hpp>

#include "FFTBuff.h"
#include "Logger.h"


#define MAGIC_COEFFICIENT 33

namespace Muvi {

    RendererGraph::RendererGraph(renderer_config_t config) {
        m_config = config;
        cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
        raw_frame = cv::Mat(MAT_HEIGHT, CHUNK_SIZE, CV_8UC1);
        for (int i = 0; i < MAT_HEIGHT; i++) {
            for (int j = 0; j < CHUNK_SIZE; j++) {
                raw_frame.at<uchar>(MAT_HEIGHT - (i + 1), j) = 0;
            }
        }
        memset(&amplitude, 0x00, sizeof(amplitude));
        cv::cvtColor(raw_frame, coloured_frame, cv::COLOR_GRAY2BGR);
        cv::resize(coloured_frame, coloured_frame,
                   cv::Size(m_config.width, m_config.height), 0, 0,
                   cv::INTER_CUBIC);
    }

    void RendererGraph::Render(fft_buff_t& buff) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            amplitude[j] = (((AVERAGE_WINDOW_SIZE - 1)) * amplitude[j] /
                            AVERAGE_WINDOW_SIZE) +
                           std::abs(buff.amplitude_1[j]) / AVERAGE_WINDOW_SIZE;
            for (int i = 0; i < MAT_HEIGHT; i++) {
                raw_frame.at<uchar>(i, j) =
                    (i > (log2(amplitude[j]) * MAGIC_COEFFICIENT) ? 0 : i);
            }
        }

        cv::equalizeHist(raw_frame, raw_frame);

        cv::cvtColor(raw_frame, coloured_frame, cv::COLOR_GRAY2BGR);
        cv::applyColorMap(coloured_frame, coloured_frame, m_config.colormap);

        for (int i = 0; i < MAT_HEIGHT; i++) {
            for (int j = 0; j < CHUNK_SIZE; j++) {
                if (raw_frame.at<uchar>(i, j) == 0) {
                    coloured_frame.at<cv::Vec3b>(i, j) = {0, 0, 0};
                };
            }
        }

        cv::resize(coloured_frame, coloured_frame,
                   cv::Size(m_config.width, m_config.height), 0, 0,
                   cv::INTER_CUBIC);
        cv::flip(coloured_frame, coloured_frame, 0);
        PlotGraph();
    }

    void RendererGraph::PlotGraph(void) {
        char key = 0x00;
        cv::imshow(WINDOW_NAME, coloured_frame);
        key = (char)cv::waitKey(1);
        if (key == 'q' or key == 'Q' or key == 27) {
            exit(0);
        }
    }

    void RendererGraph::HandleUI(void) { PlotGraph(); }

    RendererGraph::~RendererGraph() {}

};  // namespace Muvi