#pragma once

#include <AudioBuff.h>
#include <MuviConfig.h>
#include <ffaudio/audio.h>

#include <boost/circular_buffer.hpp>

namespace Muvi {
    class AudioLoopback {
       private:
        const ffaudio_interface *audio_interface;
        ffaudio_buf *audio_buf;
        ffaudio_conf audio_conf;
        void *buffer;
        boost::circular_buffer<float> samples_buff_chnl_1{AUDIO_BUFFER_SIZE};
        boost::circular_buffer<float> samples_buff_chnl_2{AUDIO_BUFFER_SIZE};
        bool BufferReady(void);
        void GetNewSamples(void);
        int GetCachedSamples(audiobuff_t *output);
        template <typename T>
        void FillInternalBuffer(size_t size, T *input_buffer);

       public:
        AudioLoopback(void);
        ~AudioLoopback(void);
        int ReadChunk(audiobuff_t *output);
    };
}  // namespace Muvi
