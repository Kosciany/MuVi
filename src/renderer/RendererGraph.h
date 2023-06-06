#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "FFTBuff.h"
#include "RendererWorker.h"

#define WINDOW_NAME "MuVi"
#define MAT_HEIGHT UCHAR_MAX
#define AVERAGE_WINDOW_SIZE 5

namespace Muvi {
    class RendererGraph {
       private:
        renderer_config_t m_config;
        double amplitude[CHUNK_SIZE];
        cv::Mat raw_frame;
        cv::Mat coloured_frame;
        void PlotGraph(void);

       public:
        RendererGraph(renderer_config_t config);
        ~RendererGraph();
        void HandleUI(void);
        void Render(fft_buff_t& buff);
    };
}  // namespace Muvi