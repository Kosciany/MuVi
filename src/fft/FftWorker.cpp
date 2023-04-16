#include "FftWorker.h"

#include <iostream>
#include <chrono>

#include "Logger.h"

namespace Muvi {


    void FftWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {
            unsigned int value;
            while(ProducerPop(value)) {
                MUVI_FFT_TRACE("Read {0}", value);
            }

            MUVI_FFT_INFO("Going to sleep for 1s");
            std::this_thread::sleep_for(1s);
        }
    }
} // Muvi