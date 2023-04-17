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
        void calcFFT(audiobuff_t *input, fft_buff_t *output);
        void calcDFT(audiobuff_t *input, fft_buff_t *output);
    };
} // Muvi
