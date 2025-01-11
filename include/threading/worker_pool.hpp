// include/threading/worker_pool.hpp
#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class WorkerPool {
public:
    explicit WorkerPool(size_t numThreads);
    ~WorkerPool();

    // Pas de copie
    WorkerPool(const WorkerPool&) = delete;
    WorkerPool& operator=(const WorkerPool&) = delete;

    void addJob(const std::function<void()>& job);

private:
    void workerFunction(int workerId);
    
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_jobs;
    std::mutex m_mutex;
    std::mutex m_outputMutex;  // Mutex supplémentaire pour la sortie
    std::condition_variable m_condition;
    bool m_stop;
};

#endif