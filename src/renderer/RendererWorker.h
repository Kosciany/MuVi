#pragma once
#include <thread>
#include <iostream>
#include <chrono>

#include "MuviConfig.h"
#include "FFTBuff.h"
#include "Worker.h"
#include "FftWorker.h"

namespace Muvi {
    class RendererWorker : public Worker,
                          public Consumer<fft_buff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
    public:
        RendererWorker(FftWorker& producer) : Consumer(producer) { }
        ~RendererWorker() {}

        void Run() override;
    };
} // Muvi
