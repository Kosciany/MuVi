#pragma once

#include "Worker.h"

namespace Muvi {

    class AudioLoopbackWorker : public Worker {
    public:
        AudioLoopbackWorker() {}
        ~AudioLoopbackWorker() {}

        void Run() override;
    };

} // Muvi
