#include <AudioLoopback.h>
#include <Logger.h>
#include <ffaudio/audio.h>
#include <stdlib.h>

#include <boost/circular_buffer.hpp>
#include <iostream>

#define FORMAT 0
#define SAMPLE_RATE 1
#define CHANNELS 2

namespace Muvi {

    AudioLoopback::AudioLoopback(void) {
        ffaudio_dev *current_dev = nullptr;
        int result = 0;
        const char *dev_id;
        ffaudio_init_conf config = {.app_name = NULL, .error = NULL};

        this->buffer = nullptr;
        this->audio_interface = ffaudio_default_interface();
        this->audio_interface->init(&config);
        current_dev = this->audio_interface->dev_alloc(FFAUDIO_DEV_PLAYBACK);

        while (result == 0) {
            result = this->audio_interface->dev_next(current_dev);
            if (result > -1) {
                const char *is_def = this->audio_interface->dev_info(
                    current_dev, FFAUDIO_DEV_IS_DEFAULT);
                if (is_def) {
                    dev_id = this->audio_interface->dev_info(current_dev,
                                                             FFAUDIO_DEV_ID);
                    break;
                }
            }
        }

        {
            ffuint *mix_format = (ffuint *)this->audio_interface->dev_info(
                current_dev, FFAUDIO_DEV_MIX_FORMAT);
            MUVI_AUDIO_INFO("Device format {}", mix_format[FORMAT]);
            this->audio_conf.format = mix_format[FORMAT];
            MUVI_AUDIO_INFO("Device sample rate {}", mix_format[SAMPLE_RATE]);
            this->audio_conf.sample_rate = mix_format[SAMPLE_RATE];
            MUVI_AUDIO_INFO("Device channels {}", mix_format[CHANNELS]);
            this->audio_conf.channels = mix_format[CHANNELS];
        }

        this->audio_buf = this->audio_interface->alloc();
        this->audio_conf.device_id = dev_id;

        result = this->audio_interface->open(this->audio_buf, &this->audio_conf,
                                             FFAUDIO_LOOPBACK);

        if (result == FFAUDIO_ERROR) {
            MUVI_AUDIO_ERROR("Error: {0}",
                             this->audio_interface->error(this->audio_buf));
        } else if (result == FFAUDIO_EFORMAT) {
            result = this->audio_interface->open(
                this->audio_buf, &this->audio_conf, FFAUDIO_LOOPBACK);
        }

        if (result) {
            MUVI_AUDIO_CRITICAL(
                "Critical error occurred during initialization: {0}", result);
        }
    }

    bool AudioLoopback::BufferReady(void) {
        return this->samples_buff_chnl_1.size() >= CHUNK_SIZE;
    }

    template <typename T>
    void AudioLoopback::FillInternalBuffer(size_t size, T *input_buffer) {
        T *ptr = (T *)input_buffer;
        for (int j = 0, i = 0;
             j < size / (sizeof(T) * this->audio_conf.channels); j++) {
            this->samples_buff_chnl_1.push_back((float)*(ptr + i));
            i += this->audio_conf.channels;
        }

        if (this->audio_conf.channels > 1) {
            for (int j = 0, i = (this->audio_conf.channels - 1);
                 j < size / (sizeof(T) * this->audio_conf.channels); j++) {
                this->samples_buff_chnl_2.push_back((float)*(ptr + i));
                i += this->audio_conf.channels;
            }
        }
    }

    void AudioLoopback::GetNewSamples(void) {
        int result = this->audio_interface->read(this->audio_buf,
                                                 (const void **)&this->buffer);

        if (result > 0) {
            switch (this->audio_conf.format) {
                case FFAUDIO_F_INT8: {
                    uint8_t *ptr = (uint8_t *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }

                case FFAUDIO_F_INT16: {
                    uint16_t *ptr = (uint16_t *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }

                case FFAUDIO_F_INT24: {
                    uint32_t *ptr = (uint32_t *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }

                case FFAUDIO_F_INT24_4: {
                    uint32_t *ptr = (uint32_t *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }

                case FFAUDIO_F_INT32: {
                    uint32_t *ptr = (uint32_t *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }

                case FFAUDIO_F_FLOAT32: {
                    float *ptr = (float *)this->buffer;
                    this->FillInternalBuffer(result, ptr);
                    break;
                }
            }
        }
        return;
    }

    int AudioLoopback::GetCachedSamples(audiobuff_t *output) {
        if (this->samples_buff_chnl_1.size() < CHUNK_SIZE) {
            return -1;
        }

        for (int i = 0; i < CHUNK_SIZE; i++) {
            output->first_channel[i] = this->samples_buff_chnl_1.front();
            this->samples_buff_chnl_1.pop_front();
            if (this->audio_conf.channels > 1) {
                output->second_channel[i] = this->samples_buff_chnl_2.front();
                this->samples_buff_chnl_2.pop_front();
            }
        }
        return 0;
    }

    int AudioLoopback::ReadChunk(audiobuff_t *output) {
        int result = 0;

        if (output == nullptr) {
            return -1;
        }

        memset(output, 0x00, sizeof(audiobuff_t));

        if (!BufferReady()) {
            GetNewSamples();
        }

        result = GetCachedSamples(output);

        output->channels = this->audio_conf.channels;
        output->frequency = this->audio_conf.sample_rate;

        if (result < 0) {
            return -1;
        }

        return 0;
    }

    AudioLoopback::~AudioLoopback(void) {
        this->audio_interface->free(audio_buf);
    }
}  // namespace Muvi
