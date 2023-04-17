#include "FftWorker.h"

#include <iostream>
#include <iomanip>
#include <chrono>

#include "Logger.h"

namespace Muvi {


    void FftWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {
            audiobuff_t value;
            while(ProducerPop(value)) {
                MUVI_FFT_TRACE("Read {0}", value);
            }
            std::this_thread::sleep_for(50ms);
            MUVI_FFT_INFO("Going to sleep for 1s");
            std::this_thread::sleep_for(1s);
        }
    }
} // Muvi
