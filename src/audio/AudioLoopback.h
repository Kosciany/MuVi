#pragma once

#include <ffaudio/audio.h>
#include <AudioBuff.h>

namespace Muvi{
    class AudioLoopback{
        private:
            const ffaudio_interface *audio_interface;
            ffaudio_buf *audio_buf;
            ffaudio_conf audio_conf;
            void *buffer;
        public:
            AudioLoopback(void);
            ~AudioLoopback(void);
            int ReadChunk(audiobuff_t* output);
    };
}
