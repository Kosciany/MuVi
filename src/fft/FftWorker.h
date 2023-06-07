#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "AudioBuff.h"
#include "AudioLoopbackWorker.h"
#include "FftBuff.h"
#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {
    class FftWorker
        : public Worker,
          public Consumer<audiobuff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS>,
          public Producer<fft_buff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
       public:
        FftWorker(AudioLoopbackWorker& producer) : Consumer(producer) {}
        ~FftWorker() {}

        void Run() override;
    };
}  // namespace Muvi
