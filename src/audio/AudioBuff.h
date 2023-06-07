#pragma once

#include <MuviConfig.h>

namespace Muvi {
    typedef struct {
        float first_channel[CHUNK_SIZE];
        float second_channel[CHUNK_SIZE];
        int channels;
        unsigned int frequency;
    } audiobuff_t;
}  // namespace Muvi
