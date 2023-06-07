#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "AudioBuff.h"
#include "AudioLoopbackWorker.h"
#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {
    class FftCalc {
       public:
        FftCalc();
        void calcFFT(audiobuff_t *input, fft_buff_t *output);
        void calcDFT(audiobuff_t *input, fft_buff_t *output);
    };
}  // namespace Muvi
