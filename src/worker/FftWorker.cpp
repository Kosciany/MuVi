#include "FftWorker.h"

#include <iostream>
#include <chrono>

namespace Muvi {

    void FftWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {

            /* Dummy task */
            for(int i=0; i<3; ++i) {
                std::cout << "FFT task worker\n";
                std::this_thread::sleep_for(1s);
            }
            SetRunningState(false);
        }
    }
} // Muvi