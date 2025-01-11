#include "threading/thread.hpp"
#include "threading/thread_safe_iostream.hpp"

Thread::Thread(const std::string& name, std::function<void()> functToExecute)
    : m_name(name), m_function(std::move(functToExecute)), m_thread(nullptr)
{
}

Thread::~Thread()
{
    stop();
}

void Thread::executeFunction()
{
    // Définir le préfixe
    threadSafeCout.setPrefix("[" + m_name + "] ");
    
    // S'assurer que le préfixe est complètement défini avant d'exécuter la fonction
    std::this_thread::yield();
    
    // Exécuter la fonction
    m_function();
}

void Thread::start()
{
    if (!m_thread)
    {
        m_thread = std::make_unique<std::thread>(&Thread::executeFunction, this);
    }
}

void Thread::stop()
{
    if (m_thread && m_thread->joinable())
    {
        m_thread->join();
        m_thread = nullptr;
    }
}