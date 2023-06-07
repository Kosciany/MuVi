#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "FFTBuff.h"
#include "FftWorker.h"
#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {

    typedef struct rendered_config{
        int colormap;
        int width;
        int height;
    } renderer_config_t;

    class RendererWorker
        : public Worker,
          public Consumer<fft_buff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
       public:
        RendererWorker(FftWorker& producer, renderer_config_t config) : Consumer(producer) {m_config = config;};
        ~RendererWorker() {}

        void Run() override;
       private:
        renderer_config_t m_config;
    };
}  // namespace Muvi
