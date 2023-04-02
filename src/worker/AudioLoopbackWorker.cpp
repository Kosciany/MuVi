#include "AudioLoopbackWorker.h"

#include <iostream>
#include <chrono>

namespace Muvi {

    void AudioLoopbackWorker::Run() {
        using namespace std::chrono_literals;

        while(IsRunning()) {

            /* Dummy task */
            for(int i=0; i<8; ++i) {
                std::cout << "Audio task worker\n";
                std::this_thread::sleep_for(500ms);
            }
            SetRunningState(false);
        }
    }
} // Muvi