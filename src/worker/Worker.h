#pragma once
#include <thread>

namespace Muvi {

    class Worker {
    public:
        Worker() : m_IsRunning{true} {}
        ~Worker() {}

        inline bool IsRunning() const { return m_IsRunning; }
        inline void SetRunningState(bool state) { m_IsRunning = state; }

        virtual void Run() = 0;
        void Spawn() { m_Thread = std::thread([this] { Run(); }); }
        void Join() { m_Thread.join(); }

    private:
        bool m_IsRunning;
        std::thread m_Thread;
    };

} // Muvi
