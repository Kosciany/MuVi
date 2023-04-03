#pragma once

#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {

    class AudioLoopbackWorker : public Worker<unsigned int, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
    public:
        AudioLoopbackWorker() {}
        ~AudioLoopbackWorker() {}

        void Run() override;
    };

} // Muvi
