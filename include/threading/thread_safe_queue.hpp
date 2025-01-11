#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <stdexcept>

template <typename TType>
class ThreadSafeQueue
{
private:
    // Mutex pour protéger l'accès concurrent à la file
    mutable std::mutex mutex;

    // Conteneur pour stocker les éléments de la file
    std::queue<TType> data;

public:
    // Constructeur par défaut
    ThreadSafeQueue() = default;

    // Empêche la copie de l'objet (constructeur et opérateur d'affectation supprimés)
    ThreadSafeQueue(const ThreadSafeQueue &) = delete;
    ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

    // Ajoute un élément à la fin de la file
    void push_back(const TType &newElement)
    {
        // Protège l'accès à la file avec un verrou
        std::lock_guard<std::mutex> lock(mutex);
        data.push(newElement);
    }

    // Ajoute un élément au début de la file
    void push_front(const TType &newElement)
    {
        // Protège l'accès à la file avec un verrou
        std::lock_guard<std::mutex> lock(mutex);

        // Crée une file temporaire pour insérer l'élément au début
        std::queue<TType> tempQueue;
        tempQueue.push(newElement);

        // Déplace les éléments existants dans la nouvelle file
        while (!data.empty())
        {
            tempQueue.push(data.front());
            data.pop();
        }

        // Remplace la file existante par la nouvelle
        data = std::move(tempQueue);
    }

    // Retire et retourne l'élément en début de file
    TType pop_front()
    {
        // Protège l'accès à la file avec un verrou
        std::lock_guard<std::mutex> lock(mutex);

        // Vérifie si la file est vide
        if (data.empty())
        {
            throw std::runtime_error("Queue is empty");
        }

        // Récupère et supprime l'élément en tête
        TType value = data.front();
        data.pop();
        return value;
    }

    // Retire et retourne l'élément en fin de file
    TType pop_back()
    {
        // Protège l'accès à la file avec un verrou
        std::lock_guard<std::mutex> lock(mutex);

        // Vérifie si la file est vide
        if (data.empty())
        {
            throw std::runtime_error("Queue is empty");
        }

        // Crée une file temporaire pour reconstruire la file sans le dernier élément
        std::queue<TType> tempQueue;
        TType value;

        while (!data.empty())
        {
            if (data.size() == 1)
            {
                // Récupère le dernier élément
                value = data.front();
            }
            else
            {
                tempQueue.push(data.front());
            }
            data.pop();
        }

        // Remplace la file existante par la nouvelle
        data = std::move(tempQueue);

        return value;
    }

    // Vérifie si la file est vide
    bool empty() const
    {
        // Protège l'accès à la file avec un verrou
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }
};

#endif // THREAD_SAFE_QUEUE_HPP
