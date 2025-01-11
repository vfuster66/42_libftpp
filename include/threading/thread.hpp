// include/threading/thread.hpp
#ifndef THREAD_HPP
#define THREAD_HPP

#include <string>
#include <functional>
#include <thread>
#include <memory>

class Thread {
public:
    Thread(const std::string& name, std::function<void()> functToExecute);
    ~Thread();

    // Interdire la copie
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    void start();
    void stop();

private:
    void executeFunction();
    std::string m_name;
    std::function<void()> m_function;
    std::unique_ptr<std::thread> m_thread;
};

#endif