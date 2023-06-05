#pragma once

#include "AudioBuff.h"
#include "MuviConfig.h"
#include "Worker.h"

namespace Muvi {

    class AudioLoopbackWorker
        : public Worker,
          public Producer<audiobuff_t, MUVI_CFG_WORKER_BUF_SIZE_ELEMS> {
       public:
        AudioLoopbackWorker() {}
        ~AudioLoopbackWorker() {}

        void Run() override;
    };

}  // namespace Muvi
