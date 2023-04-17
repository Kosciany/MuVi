#include "AudioLoopbackWorker.h"

#include <iostream>
#include <chrono>

#include "AudioLoopback.h"
#include "Logger.h"

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
                    MUVI_AUDIO_TRACE("Pushing {0}", buffer[i]);
                    if(!Push((unsigned int)buffer[i])) {
                        MUVI_AUDIO_WARN("Queue is full!");
                        break;
                    }
                }

                MUVI_AUDIO_INFO("Going to sleep for 1s");
                std::this_thread::sleep_for(1s);
            }
        } while(1);
    }
} // Muvi