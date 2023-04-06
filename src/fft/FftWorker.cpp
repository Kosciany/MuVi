#include "FftWorker.h"

#include <iostream>
#include <iomanip>
#include <chrono>

namespace Muvi {


    void FftWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {
            audiobuff_t value;
            while(ProducerPop(value)) {
                std::cout << "[FFT Worker] read " << value.channels << std::fixed << std::setw(10) << std::setprecision(5) << value.first_channel[0] << std::endl;
            }
            std::this_thread::sleep_for(50ms);
        }
    }
} // Muvi
