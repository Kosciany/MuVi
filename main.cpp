// Your First C++ Program

#include <iostream>
#include <stdlib.h>
#include <ffaudio/audio.h>

int main() {
    ffaudio_init_conf config = {
        .app_name = NULL,
        .error = NULL
    };
    const ffaudio_interface* dummy = ffaudio_default_interface();
    ffaudio_default_interface()->init(&config);
    ffaudio_dev *example_dev = ffaudio_default_interface()->dev_alloc(FFAUDIO_DEV_PLAYBACK);
    short res = 0;
    const char *dev_id;
    while (res == 0)
    {
        res = ffaudio_default_interface()->dev_next(example_dev);
        if (res > -1 ){
            printf("%s",ffaudio_default_interface()->dev_info(example_dev, FFAUDIO_DEV_NAME));
            const char *is_def = ffaudio_default_interface()->dev_info(example_dev, FFAUDIO_DEV_IS_DEFAULT);
            if(is_def){
                dev_id = ffaudio_default_interface()->dev_info(example_dev, FFAUDIO_DEV_ID);
                printf("<---- It is default dev");
                break;
            }
            printf("\n");
        }
    }
    ffaudio_buf *audio_buf = ffaudio_default_interface()->alloc();
    ffaudio_conf audio_conf;
    audio_conf.device_id = dev_id;
    res = ffaudio_default_interface()->open(audio_buf, &audio_conf, FFAUDIO_LOOPBACK );//| FFAUDIO_O_NONBLOCK );
    if(res == FFAUDIO_ERROR)
    {
        printf("Error: %s \n",ffaudio_default_interface()->error(audio_buf));
    }
    else if (res == FFAUDIO_EFORMAT)
    {
        res = ffaudio_default_interface()->open(audio_buf, &audio_conf, FFAUDIO_LOOPBACK | FFAUDIO_O_NONBLOCK );
    }

    uint32_t *buffer;
    while(true)
    {
        res = ffaudio_default_interface()->read(audio_buf, (const void**) &buffer);
        printf("%d", res);
        if(res > 0)
        {
            FILE *fptr;
            fptr = fopen("D:\\Programowanie\\audio_test\\audioarray.txt","w");
            for(int i=0; i < res/sizeof(uint32_t); i++)
            {
                fprintf(fptr,"%zu\n",buffer[i]);
            }
            fclose(fptr);
            break;
        }
    }
    ffaudio_default_interface()->free(audio_buf);
    return 0;
}