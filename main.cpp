// Your First C++ Program

#include <iostream>
#include <stdlib.h>
#include <ffaudio/audio.h>
#include <AudioLoopback.h>

int main() {
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

    return 0;
}