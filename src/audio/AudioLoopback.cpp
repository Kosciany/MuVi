#include <iostream>
#include <stdlib.h>

#include <ffaudio/audio.h>
#include <AudioLoopback.h>
#include <Logger.h>


namespace Muvi {

    template <typename T>
    void fill_buffer(audiobuff_t *output_buffer, size_t size, T *input_buffer)
    {
        output_buffer->samples = size/(sizeof(T) * output_buffer->channels);
        if (output_buffer->samples > (sizeof(output_buffer->first_channel)/output_buffer->first_channel[0])){
            MUVI_AUDIO_ERROR("Buffer for samples is too small");
            output_buffer->samples = (sizeof(output_buffer->first_channel)/output_buffer->first_channel[0]);
        }

        T *ptr = (T *) input_buffer;
        for(int j=0, i=0; j < output_buffer->samples; j++) {
            output_buffer->first_channel[j] = (float) *(ptr+i);
            i += output_buffer->channels;
        }
        if(output_buffer->channels > 1) {
            for(int j=0, i=(output_buffer->channels-1); j < output_buffer->samples; j++) {
                output_buffer->second_channel[j] = (float) *(ptr+i);
                i += output_buffer->channels;
            }
        }
    }

    AudioLoopback::AudioLoopback(void) {
        ffaudio_dev *current_dev = nullptr;
        short res = 0;
        const char *dev_id;
        ffaudio_init_conf config = {
            .app_name = NULL,
            .error = NULL
        };

        this->buffer = nullptr;
        this->audio_interface = ffaudio_default_interface();
        this->audio_interface->init(&config);
        current_dev = this->audio_interface->dev_alloc(FFAUDIO_DEV_PLAYBACK);

        while (res == 0) {
            res = this->audio_interface->dev_next(current_dev);
            if (res > -1 ) {
                const char *is_def = this->audio_interface->dev_info(current_dev, FFAUDIO_DEV_IS_DEFAULT);
                if(is_def) {
                    dev_id = this->audio_interface->dev_info(current_dev, FFAUDIO_DEV_ID);
                    break;
                }
            }
        }

        this->audio_buf = this->audio_interface->alloc();
        this->audio_conf.device_id = dev_id;

        // TODO: avoid generating FFAUDIO_EFORMAT in the first place
        res = this->audio_interface->open(this->audio_buf , &this->audio_conf, FFAUDIO_LOOPBACK | FFAUDIO_O_NONBLOCK);

        if(res == FFAUDIO_ERROR) {
            MUVI_AUDIO_ERROR("Error: {0}", this->audio_interface->error(this->audio_buf));
        }
        else if (res == FFAUDIO_EFORMAT)
        {
            res = this->audio_interface->open(this->audio_buf , &this->audio_conf, FFAUDIO_LOOPBACK | FFAUDIO_O_NONBLOCK);
        }
    }

    int AudioLoopback::ReadChunk(audiobuff_t* output) {
        int result = 0;

        if(output == nullptr) {
            return -1;
        }

        memset(output, 0x00, sizeof(audiobuff_t));

        result = this->audio_interface->read(this->audio_buf, (const void**) &this->buffer);

        if(result > 0) {
            output->channels = this->audio_conf.channels;
            output->frequency = this->audio_conf.sample_rate;
            switch(this->audio_conf.format) {
                case FFAUDIO_F_INT8: {
                    uint8_t *ptr =  (uint8_t *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }

                case FFAUDIO_F_INT16: {
                    uint16_t *ptr =  (uint16_t *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }

                case FFAUDIO_F_INT24: {
                    uint32_t *ptr =  (uint32_t *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }

                case FFAUDIO_F_INT24_4: {
                    uint32_t *ptr =  (uint32_t *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }

                case FFAUDIO_F_INT32: {
                    uint32_t *ptr =  (uint32_t *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }

                case FFAUDIO_F_FLOAT32: {
                    float *ptr =  (float *) this->buffer;
                    fill_buffer(output, result, ptr);
                    break;
                }
            }
            output->period_ms = output->frequency/output->samples;
        }
        if(result < 0) {
            return -1;
        }

        return 0;
    }

    AudioLoopback::~AudioLoopback(void) {
        this->audio_interface->free(audio_buf);
    }
}
