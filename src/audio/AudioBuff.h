#pragma once

#include <MuviConfig.h>

namespace Muvi{
    typedef struct{
        float first_channel[AUDIO_BUFFER_SIZE];
        float second_channel[AUDIO_BUFFER_SIZE];
        unsigned int samples;
        int channels;
        unsigned int frequency;
        unsigned int period_ms;
    } audiobuff_t;
}
