#include "FftWorker.h"

#include <iostream>
#include <chrono>

namespace Muvi {


    void FftWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {
            unsigned int value;
            while(ProducerPop(value)) {
                std::cout << "[FFT Worker] read " << value << std::endl;
            }

            std::cout << "[FFT Worker] Going to sleep for 1s\n";
            std::this_thread::sleep_for(1s);
        }
    }
} // Muvi