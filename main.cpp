#include <iostream>
#include <stdlib.h>

#include "Logger.h"
#include "FftWorker.h"
#include "AudioLoopbackWorker.h"

int main() {
    MuVi::Logger::Init();

    Muvi::AudioLoopbackWorker audioLoopbackWorker;
    audioLoopbackWorker.Spawn();

    Muvi::FftWorker fftWorker(audioLoopbackWorker);
    fftWorker.Spawn();

    audioLoopbackWorker.Join();
    fftWorker.Join();

    return 0;
}