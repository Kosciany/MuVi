#pragma once
#include <thread>
#include <iostream>
#include <chrono>

#include "MuviConfig.h"
#include "Worker.h"
#include "AudioBuff.h"
#include "FftBuff.h"
#include "AudioLoopbackWorker.h"

namespace Muvi {
    class FftWorker : public Worker,
                      public Consumer<audiobuff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS>,
                      public Producer<fft_buff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
    public:
        FftWorker(AudioLoopbackWorker& producer) : Consumer(producer) { }
        ~FftWorker() {}

        void Run() override;
    };
} // Muvi
