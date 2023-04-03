#include <iostream>
#include <stdlib.h>

#include "FftWorker.h"
#include "AudioLoopbackWorker.h"

int main() {
    Muvi::FftWorker fftWorker;
    fftWorker.Spawn();

    Muvi::AudioLoopbackWorker audioLoopbackWorker;
    audioLoopbackWorker.Spawn();

    audioLoopbackWorker.Join();
    fftWorker.Join();

    return 0;
}