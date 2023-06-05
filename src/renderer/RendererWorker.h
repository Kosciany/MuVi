#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "FFTBuff.h"
#include "FftWorker.h"
#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {
    class RendererWorker
        : public Worker,
          public Consumer<fft_buff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
       public:
        RendererWorker(FftWorker& producer) : Consumer(producer) {}
        ~RendererWorker() {}

        void Run() override;
    };
}  // namespace Muvi
