#ifndef THREAD_HPP
#define THREAD_HPP

#include <string>
#include <functional>
#include <thread>
#include <memory>

class Thread {
public:
    // Constructeur pour initialiser un thread avec un nom et une fonction à exécuter
    Thread(const std::string& name, std::function<void()> functToExecute);

    // Destructeur pour nettoyer les ressources utilisées par le thread
    ~Thread();

    // Interdire la copie pour éviter des comportements inattendus liés à la gestion des threads
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    // Démarre l'exécution de la fonction associée au thread
    void start();

    // Arrête le thread (implémentation dépendante du contexte)
    void stop();

private:
    // Fonction privée appelée par le thread lors de son exécution
    void executeFunction();

    // Nom du thread, utilisé pour identifier ou déboguer les threads
    std::string m_name;

    // Fonction à exécuter par le thread
    std::function<void()> m_function;

    // Gestionnaire pour encapsuler le thread et gérer sa durée de vie
    std::unique_ptr<std::thread> m_thread;
};

#endif
