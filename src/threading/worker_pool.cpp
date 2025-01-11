// src/threading/worker_pool.cpp
#include "threading/worker_pool.hpp"
#include "threading/thread_safe_iostream.hpp"
#include <sstream>

WorkerPool::WorkerPool(size_t numThreads) : m_stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        m_workers.emplace_back(&WorkerPool::workerFunction, this, i);
    }
}

WorkerPool::~WorkerPool() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_stop = true;
    }
    m_condition.notify_all();

    for (auto& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void WorkerPool::addJob(const std::function<void()>& job) {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_jobs.push(job);
    }
    m_condition.notify_one();
}

void WorkerPool::workerFunction(int workerId) {
    std::stringstream prefix;
    prefix << "[Worker " << workerId << "] ";
    threadSafeCout.setPrefix(prefix.str());

    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this]() { 
                return m_stop || !m_jobs.empty(); 
            });

            if (m_stop && m_jobs.empty()) {
                return;
            }

            job = std::move(m_jobs.front());
            m_jobs.pop();
        }

        // Exécution du job de manière thread-safe
        std::lock_guard<std::mutex> outputLock(m_outputMutex);
        job();
    }
}