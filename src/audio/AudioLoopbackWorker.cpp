#include <iostream>
#include <chrono>
#include "AudioLoopbackWorker.h"
#include "AudioLoopback.h"
#include "Logger.h"

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
                    MUVI_AUDIO_TRACE("Pushing {0}", buffer[i]);
                        MUVI_AUDIO_WARN("Queue is full!");
                }
                // std::cout << "[AudioLoopback Worker] Going to sleep for 1s\n";
                MUVI_AUDIO_INFO("Going to sleep for 1s");
                std::this_thread::sleep_for(1s);
            }
        } while(1);
    }
} // Muvi
