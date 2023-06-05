#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "FFTBuff.h"

#define WINDOW_NAME "MuVi"
#define MAT_HEIGHT UCHAR_MAX
#define AVERAGE_WINDOW_SIZE 5

namespace Muvi {
    class RendererGraph {
       private:
        double amplitude[CHUNK_SIZE];
        cv::Mat raw_frame;
        cv::Mat coloured_frame;
        void PlotGraph(void);

       public:
        RendererGraph();
        ~RendererGraph();
        void HandleUI(void);
        void Render(fft_buff_t& buff);
    };
}  // namespace Muvi