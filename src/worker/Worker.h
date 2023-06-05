#pragma once
#include <boost/lockfree/spsc_queue.hpp>
#include <semaphore>
#include <thread>

namespace Muvi {

    class Worker {
       public:
        Worker() : m_IsRunning{true} {}
        ~Worker() {}

        inline bool IsRunning() const { return m_IsRunning; }
        inline void SetRunningState(bool state) { m_IsRunning = state; }

        virtual void Run() = 0;
        void Spawn() {
            m_Thread = std::thread([this] { Run(); });
        }
        void Join() { m_Thread.join(); }

       private:
        bool m_IsRunning;
        std::thread m_Thread;
    };

    template <typename P, int BUF_ELEMS>
    class Producer {
       private:
       public:
        std::binary_semaphore m_Semaphore;
        boost::lockfree::spsc_queue<P, boost::lockfree::capacity<BUF_ELEMS>>
            m_Queue;
        Producer() : m_Semaphore{0} {}
        ~Producer() {}

       protected:
        /* Returns true if operation was successful */
        bool Produce(P value) {
            m_Semaphore.release();
            return m_Queue.push(value);
        }
    };

    template <typename C, int BUF_ELEMS>
    class Consumer {
       private:
        std::thread m_Thread;
        Producer<C, BUF_ELEMS> *m_Producer = nullptr;

       public:
        Consumer(Producer<C, BUF_ELEMS> &producer) : m_Producer{&producer} {}
        ~Consumer() {}

        /* Returns true if operation was successful,
         * false if ringbuffer was empty */
        bool Consume(C &value) { return m_Producer->m_Queue.pop(value); }
        void waitForProduct() { m_Producer->m_Semaphore.acquire(); }
    };

}  // namespace Muvi
