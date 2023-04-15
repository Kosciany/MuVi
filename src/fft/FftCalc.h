#pragma once
#include <thread>
#include <iostream>
#include <chrono>

#include "MuviConfig.h"
#include "Worker.h"
#include "AudioBuff.h"
#include "AudioLoopbackWorker.h"

namespace Muvi {
    class FftCalc {
    public:
        FftCalc();
        void calc(audiobuff_t *input, fft_buff_t *output);
        void slowFFT(audiobuff_t *input, fft_buff_t *output);
    };
} // Muvi
