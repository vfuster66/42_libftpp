// include/threading/persistent_worker.hpp
#ifndef PERSISTENT_WORKER_HPP
#define PERSISTENT_WORKER_HPP

#include <thread>
#include <string>
#include <map>
#include <functional>
#include <mutex>
#include <atomic>

class PersistentWorker {
public:
    PersistentWorker();
    ~PersistentWorker();

    // Pas de copie
    PersistentWorker(const PersistentWorker&) = delete;
    PersistentWorker& operator=(const PersistentWorker&) = delete;

    void addTask(const std::string& name, const std::function<void()>& jobToExecute);
    void removeTask(const std::string& name);

private:
    void workerFunction();

    std::thread m_thread;
    std::map<std::string, std::function<void()>> m_tasks;
    std::mutex m_mutex;
    std::atomic<bool> m_stop;
};

#endif