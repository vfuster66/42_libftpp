// src/threading/persistent_worker.cpp
#include "threading/persistant_worker.hpp"
#include "threading/thread_safe_iostream.hpp"

PersistentWorker::PersistentWorker() : m_stop(false) {
    m_thread = std::thread(&PersistentWorker::workerFunction, this);
}

PersistentWorker::~PersistentWorker() {
    m_stop = true;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void PersistentWorker::addTask(const std::string& name, const std::function<void()>& jobToExecute) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks[name] = jobToExecute;
}

void PersistentWorker::removeTask(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.erase(name);
}

void PersistentWorker::workerFunction() {
    while (!m_stop) {
        std::map<std::string, std::function<void()>> tasks;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            tasks = m_tasks;
        }

        for (const auto& task : tasks) {
            if (!m_stop) {
                task.second();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}