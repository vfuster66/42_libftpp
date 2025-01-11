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

class Server
{
private:
    size_t port;
    std::unordered_map<long long, int> clients; // Simuler les clients connectés
    std::unordered_map<int, std::function<void(long long &, const Message &)>> actions; // Actions par type de message
    std::queue<std::pair<long long, Message>> messages; // File des messages reçus
    std::mutex messageMutex;
    std::atomic<bool> running = false;
    std::thread listenerThread;
    size_t maxClients = 5; //

    void listenForClients();

public:
    Server();
    ~Server();

    void start(const size_t &p_port);
    void stop();
    void defineAction(const int &messageType, const std::function<void(long long &, const Message &)> &action);
    void sendTo(const Message &message, long long clientID);
    void sendToArray(const Message &message, const std::vector<long long> &clientIDs);
    void sendToAll(const Message &message);
    void update();
};

#endif // SERVER_HPP
