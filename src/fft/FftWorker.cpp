#include "FftWorker.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "FftBuff.h"
#include "FftCalc.h"
#include "Logger.h"

namespace Muvi {

    void FftWorker::Run() {
        using namespace std::chrono_literals;
        FftCalc fftcalc = FftCalc();
        fft_buff_t buff;
        while (IsRunning()) {
            audiobuff_t value;
            while (Consume(value)) {
                MUVI_FFT_TRACE("Samples read");
                fftcalc.calcFFT(&value, &buff);
                Produce(buff);
            }
            waitForProduct();
        }
    }
}  // namespace Muvi
