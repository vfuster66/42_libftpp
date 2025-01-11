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
    // Constructeur par défaut
    PersistentWorker();

    // Destructeur pour nettoyer correctement les ressources
    ~PersistentWorker();

    // Supprime la possibilité de copier l'objet PersistentWorker
    PersistentWorker(const PersistentWorker&) = delete;
    PersistentWorker& operator=(const PersistentWorker&) = delete;

    // Ajoute une tâche au pool, associée à un nom unique
    void addTask(const std::string& name, const std::function<void()>& jobToExecute);

    // Supprime une tâche existante du pool à l'aide de son nom
    void removeTask(const std::string& name);

private:
    // Fonction exécutée par le thread, qui gère les tâches persistantes
    void workerFunction();

    // Thread dédié au traitement des tâches
    std::thread m_thread;

    // Liste des tâches actives associées à leurs noms
    std::map<std::string, std::function<void()>> m_tasks;

    // Mutex pour protéger l'accès concurrent à la liste des tâches
    std::mutex m_mutex;

    // Indicateur atomique pour arrêter le thread de manière sûre
    std::atomic<bool> m_stop;
};

#endif // PERSISTENT_WORKER_HPP
