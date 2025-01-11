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
    // Constructeur pour initialiser le pool de travailleurs avec un nombre spécifique de threads
    explicit WorkerPool(size_t numThreads);

    // Destructeur pour nettoyer les threads et s'assurer que tous les travaux sont terminés
    ~WorkerPool();

    // Empêche la copie pour éviter des comportements inattendus dans la gestion des threads
    WorkerPool(const WorkerPool&) = delete;
    WorkerPool& operator=(const WorkerPool&) = delete;

    // Ajoute un travail (job) à la file d'attente des tâches
    void addJob(const std::function<void()>& job);

private:
    // Fonction exécutée par chaque thread pour traiter les tâches
    void workerFunction(int workerId);

    // Vecteur pour stocker les threads du pool
    std::vector<std::thread> m_workers;

    // File d'attente des travaux à exécuter
    std::queue<std::function<void()>> m_jobs;

    // Mutex pour protéger l'accès concurrent à la file de travaux
    std::mutex m_mutex;

    // Mutex séparé pour synchroniser l'accès aux sorties ou autres sections critiques
    std::mutex m_outputMutex;

    // Condition variable pour notifier les threads lorsqu'un nouveau travail est disponible
    std::condition_variable m_condition;

    // Indicateur pour signaler aux threads d'arrêter leur exécution
    bool m_stop;
};

#endif
