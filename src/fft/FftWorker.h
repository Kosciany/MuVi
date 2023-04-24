#pragma once
#include <thread>
#include <iostream>
#include <chrono>

#include "MuviConfig.h"
#include "Worker.h"
#include "AudioBuff.h"
#include "AudioLoopbackWorker.h"

namespace Muvi {
    class FftWorker : public Worker<audiobuff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
    public:
        FftWorker(AudioLoopbackWorker& producer) : Worker(producer) { }
        FftWorker() : Worker() {}

        void Run() override;
    };
} // Muvi
