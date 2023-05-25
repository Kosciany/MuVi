#include <iostream>
#include <stdlib.h>

#include "Logger.h"
#include "FftWorker.h"
#include "AudioLoopbackWorker.h"
#include "RendererWorker.h"

int main() {
    MuVi::Logger::Init();

    Muvi::AudioLoopbackWorker audioLoopbackWorker;
    audioLoopbackWorker.Spawn();

    Muvi::FftWorker fftWorker(audioLoopbackWorker);
    fftWorker.Spawn();

    Muvi::RendererWorker rendererWorker(fftWorker);
    rendererWorker.Spawn();

    // audioLoopbackWorker.Join();
    // fftWorker.Join();
    rendererWorker.Join();

    return 0;
}