#include <iostream>
#include <stdlib.h>

#include "FftWorker.h"
#include "AudioLoopbackWorker.h"

int main() {
    Muvi::AudioLoopbackWorker audioLoopbackWorker;
    audioLoopbackWorker.Spawn();

    Muvi::FftWorker fftWorker(audioLoopbackWorker);
    fftWorker.Spawn();

    audioLoopbackWorker.Join();
    fftWorker.Join();

    return 0;
}