#include "threading/persistant_worker.hpp"
#include "threading/thread_safe_iostream.hpp"

// Constructeur : Initialise le thread et démarre la boucle de travail
PersistentWorker::PersistentWorker() : m_stop(false) {
    // Crée et lance un thread qui exécute la méthode workerFunction
    m_thread = std::thread(&PersistentWorker::workerFunction, this);
}

// Destructeur : Arrête le thread proprement
PersistentWorker::~PersistentWorker() {
    // Indique au thread de s'arrêter
    m_stop = true;
    // Attend que le thread se termine s'il est toujours actif
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

// Ajoute une tâche au pool avec un nom unique
void PersistentWorker::addTask(const std::string& name, const std::function<void()>& jobToExecute) {
    // Protéger l'accès concurrent à m_tasks avec un mutex
    std::lock_guard<std::mutex> lock(m_mutex);
    // Ajoute ou remplace une tâche dans la map
    m_tasks[name] = jobToExecute;
}

// Supprime une tâche par son nom
void PersistentWorker::removeTask(const std::string& name) {
    // Protéger l'accès concurrent à m_tasks avec un mutex
    std::lock_guard<std::mutex> lock(m_mutex);
    // Supprime la tâche correspondante dans la map
    m_tasks.erase(name);
}

// Fonction exécutée par le thread pour gérer les tâches
void PersistentWorker::workerFunction() {
    // Continue tant que m_stop est faux
    while (!m_stop) {
        std::map<std::string, std::function<void()>> tasks;
        {
            // Protéger l'accès concurrent à m_tasks pour copier son contenu
            std::lock_guard<std::mutex> lock(m_mutex);
            tasks = m_tasks; // Crée une copie locale des tâches à exécuter
        }

        // Exécute chaque tâche copiée
        for (const auto& task : tasks) {
            // Vérifie si le thread doit s'arrêter avant d'exécuter la tâche
            if (!m_stop) {
                task.second(); // Appelle la fonction associée à la tâche
            }
        }

        // Pause pour éviter d'utiliser 100 % du CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
