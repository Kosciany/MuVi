#pragma once
#include <thread>
#include <boost/lockfree/spsc_queue.hpp>

namespace Muvi {

    template<typename T, int BUF_ELEMS>
    class Worker {
    public:
        Worker(Worker& producer) : m_IsRunning{true}, m_Producer{&producer} {}
        Worker() : m_IsRunning{true} {}
        ~Worker() {}

        inline bool IsRunning() const { return m_IsRunning; }
        inline void SetRunningState(bool state) { m_IsRunning = state; }

        virtual void Run() = 0;
        void Spawn() { m_Thread = std::thread([this] { Run(); }); }
        void Join() { m_Thread.join(); }

        /* Returns true if operation was successful,
         * false if ringbuffer was empty */
        bool ProducerPop(T& value) { return m_Producer->m_Queue.pop(value); }


    protected:
        /* Returns true if operation was successful */
        bool Push(T value) { return m_Queue.push(value); }

    private:
        bool m_IsRunning;
        std::thread m_Thread;
        boost::lockfree::spsc_queue<T, boost::lockfree::capacity<BUF_ELEMS>> m_Queue;
        Worker* m_Producer = nullptr;
    };

} // Muvi
