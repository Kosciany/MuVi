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
        int result = 0;
        do
        {
            result = audio.ReadChunk(&audio_buffer);
            if (!result) {
                MUVI_AUDIO_TRACE("Pushing buffer");
                if(!Push(audio_buffer)) {
                    MUVI_AUDIO_WARN("Queue is full!");
                }
            }
        } while(1);
    }
} // Muvi
