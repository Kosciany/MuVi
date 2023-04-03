#include "AudioLoopbackWorker.h"

#include <iostream>
#include <chrono>

#include "AudioLoopback.h"

namespace Muvi {

    void AudioLoopbackWorker::Run() {
        using namespace std::chrono_literals;

        AudioLoopback audio;
        int size = 0;
        uint32_t *buffer;
        int result = 0;
        do
        {
            result = audio.ReadChunk(&size, (void **) &buffer);
            if (buffer) {
                for(int i=0; i < size/sizeof(uint32_t); i++)
                {
                    std::cout <<"[AudioLoopback Worker] Pushing " << buffer[i] << std::endl;
                    if(!Push((unsigned int)buffer[i])) {
                        std::cout << "[AudioLoopback Worker] Queue is full!\n";
                        break;
                    }
                }

                std::cout << "[AudioLoopback Worker] Going to sleep for 1s\n";
                std::this_thread::sleep_for(1s);
            }
        } while(1);
    }
} // Muvi