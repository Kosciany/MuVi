#include "AudioLoopbackWorker.h"

#include <iostream>

#include "AudioLoopback.h"

namespace Muvi {

    void AudioLoopbackWorker::Run() {
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
                    printf("%zu ",buffer[i]);
                }
            }
        } while(size <= 0);
    }
} // Muvi