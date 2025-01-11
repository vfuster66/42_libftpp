#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <stdexcept>

template <typename TType>
class ThreadSafeQueue
{
private:
    mutable std::mutex mutex; // Mutex pour protéger l'accès concurrent
    std::queue<TType> data;   // Conteneur de la file

public:
    // Constructeur par défaut
    ThreadSafeQueue() = default;

    // Empêche la copie
    ThreadSafeQueue(const ThreadSafeQueue &) = delete;
    ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

    // Ajoute un élément à la fin de la file
    void push_back(const TType &newElement)
    {
        std::lock_guard<std::mutex> lock(mutex); // Protège l'accès à la file
        data.push(newElement);
    }

    // Ajoute un élément au début de la file
    void push_front(const TType &newElement)
    {
        std::lock_guard<std::mutex> lock(mutex); // Protège l'accès à la file
        std::queue<TType> tempQueue;
        tempQueue.push(newElement);
        while (!data.empty())
        {
            tempQueue.push(data.front());
            data.pop();
        }
        data = std::move(tempQueue);
    }

    // Retire et retourne l'élément en début de file
    TType pop_front()
    {
        std::lock_guard<std::mutex> lock(mutex); // Protège l'accès à la file
        if (data.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        TType value = data.front();
        data.pop();
        return value;
    }

    // Retire et retourne l'élément en fin de file
    TType pop_back()
    {
        std::lock_guard<std::mutex> lock(mutex); // Protège l'accès à la file
        if (data.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        std::queue<TType> tempQueue;
        TType value;
        while (!data.empty())
        {
            if (data.size() == 1)
            {
                value = data.front();
            }
            else
            {
                tempQueue.push(data.front());
            }
            data.pop();
        }
        data = std::move(tempQueue);
        return value;
    }

    // Vérifie si la file est vide
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex); // Protège l'accès à la file
        return data.empty();
    }
};

#endif // THREAD_SAFE_QUEUE_HPP
