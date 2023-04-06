#include <iostream>
#include <chrono>
#include "AudioLoopbackWorker.h"
#include "AudioLoopback.h"

namespace Muvi {

    void AudioLoopbackWorker::Run() {
        using namespace std::chrono_literals;

        AudioLoopback audio;
        audiobuff_t audio_buffer;
        int size = 0;
        int result = 0;
        do
        {
            result = audio.ReadChunk(&audio_buffer);
            if (!result) {
                //std::cout <<"[AudioLoopback Worker] Pushing " << audio_buffer.buff[0] << std::endl;
                if(!Push(audio_buffer)) {
                    std::cout << "[AudioLoopback Worker] Queue is full!\n";
                }
                // std::cout << "[AudioLoopback Worker] Going to sleep for 1s\n";
                std::this_thread::sleep_for(100ms);
            }
        } while(1);
    }
} // Muvi
