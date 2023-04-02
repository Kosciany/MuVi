#include <iostream>
#include <stdlib.h>

#include <ffaudio/audio.h>
#include <AudioLoopback.h>

AudioLoopback::AudioLoopback(void)
{
    this->audio_interface = ffaudio_default_interface();

    ffaudio_init_conf config = {
        .app_name = NULL,
        .error = NULL
    };

    this->audio_interface->init(&config);

    ffaudio_dev *example_dev = this->audio_interface->dev_alloc(FFAUDIO_DEV_PLAYBACK);

    short res = 0;
    const char *dev_id;
    while (res == 0)
    {
        res = this->audio_interface->dev_next(example_dev);
        if (res > -1 ){
            printf("%s",this->audio_interface->dev_info(example_dev, FFAUDIO_DEV_NAME));
            const char *is_def = this->audio_interface->dev_info(example_dev, FFAUDIO_DEV_IS_DEFAULT);
            if(is_def){
                dev_id = this->audio_interface->dev_info(example_dev, FFAUDIO_DEV_ID);
                printf("<---- It is default dev");
                break;
            }
            printf("\n");
        }
    }

    this->audio_buf = this->audio_interface->alloc();

    ffaudio_conf audio_conf;

    audio_conf.device_id = dev_id;

    res = this->audio_interface->open(this->audio_buf , &audio_conf, FFAUDIO_LOOPBACK );//| FFAUDIO_O_NONBLOCK );

    if(res == FFAUDIO_ERROR)
    {
        printf("Error: %s \n",this->audio_interface->error(this->audio_buf ));
    }
    else if (res == FFAUDIO_EFORMAT)
    {
        res = this->audio_interface->open(this->audio_buf , &audio_conf, FFAUDIO_LOOPBACK | FFAUDIO_O_NONBLOCK );
    }
}

int AudioLoopback::ReadChunk(int *size, void **output_buffer){

    uint32_t *dest, *buffer;
    *size = this->audio_interface->read(this->audio_buf, (const void**) &buffer);

    if(*size > 0)
    {
        dest = (uint32_t *) malloc(*size);
        memcpy(dest, buffer, *size);
        *output_buffer = (void *) dest; 
    }

    return 0;
}

AudioLoopback::~AudioLoopback(void)
{
    this->audio_interface->free(audio_buf);
}