#include "AudioLoopbackWorker.h"

#include <chrono>
#include <iostream>

#include "AudioLoopback.h"
#include "Logger.h"

namespace Muvi {

    void AudioLoopbackWorker::Run() {
        AudioLoopback audio;
        audiobuff_t audio_buffer;
        int result = 0;
        do {
            result = audio.ReadChunk(&audio_buffer);
            if (!result) {
                MUVI_AUDIO_TRACE("Pushing buffer");
                if (!Produce(audio_buffer)) {
                    MUVI_AUDIO_WARN("Queue is full!");
                }
            }
        } while (1);
    }
}  // namespace Muvi
