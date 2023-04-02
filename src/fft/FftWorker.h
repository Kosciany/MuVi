#pragma once
#include <thread>
#include <iostream>
#include <chrono>

#include "Worker.h"

namespace Muvi {
    class FftWorker : public Worker {
    public:
        FftWorker() {}
        ~FftWorker() {}

        void Run() override;
    };
} // Muvi
