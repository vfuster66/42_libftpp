#ifndef SERVER_HPP
#define SERVER_HPP

#include "message.hpp"
#include <unordered_map>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>

class Server {
private:
    // Port sur lequel le serveur écoute
    size_t port;

    // Simuler les clients connectés, avec leur ID et état
    std::unordered_map<long long, int> clients;

    // Actions associées aux types de messages
    std::unordered_map<int, std::function<void(long long &, const Message &)>> actions;

    // File des messages reçus avec leur ID de client
    std::queue<std::pair<long long, Message>> messages;

    // Mutex pour protéger l'accès à la file de messages
    std::mutex messageMutex;

    // Indique si le serveur est en cours d'exécution
    std::atomic<bool> running = false;

    // Thread séparé pour écouter les clients
    std::thread listenerThread;

    // Nombre maximum de clients autorisés à se connecter
    size_t maxClients = 5;

    // Écoute les nouveaux clients et gère leurs connexions
    void listenForClients();

public:
    // Constructeur par défaut
    Server();

    // Destructeur pour nettoyer correctement les ressources
    ~Server();

    // Démarre le serveur sur un port spécifique
    void start(const size_t &p_port);

    // Arrête le serveur et libère les ressources
    void stop();

    // Définit une action à exécuter pour un type spécifique de message
    void defineAction(const int &messageType, const std::function<void(long long &, const Message &)> &action);

    // Envoie un message à un client spécifique
    void sendTo(const Message &message, long long clientID);

    // Envoie un message à un ensemble de clients
    void sendToArray(const Message &message, const std::vector<long long> &clientIDs);

    // Diffuse un message à tous les clients connectés
    void sendToAll(const Message &message);

    // Traite les messages en attente dans la file
    void update();
};

#endif // SERVER_HPP
