#pragma once

#include <ffaudio/audio.h>

class AudioLoopback{
    private:
        const ffaudio_interface *audio_interface;
        ffaudio_buf *audio_buf;
    public:
        AudioLoopback(void);
        ~AudioLoopback(void);
        int ReadChunk(int *size, void **buffer);
};