// include/network/client.hpp
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "message.hpp"
#include <string>
#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>

class Client
{
private:
    std::string serverAddress;                // Adresse du serveur
    size_t serverPort;                        // Port du serveur
    std::unordered_map<int, std::function<void(const Message &)>> actions; // Actions associées aux types de message
    std::queue<Message> receivedMessages;    // File des messages reçus
    std::mutex messageMutex;                 // Mutex pour protéger la file des messages
    std::atomic<bool> connected = false;     // Indique si le client est connecté
    std::thread receiveThread;               // Thread pour recevoir les messages

    void receiveMessages();                  // Méthode pour recevoir les messages en arrière-plan

public:
    Client();
    ~Client();

    void connect(const std::string &address, const size_t &port);
    void disconnect();
    void defineAction(const int &messageType, const std::function<void(const Message &msg)> &action);
    void send(const Message &message);
    void update();
};

#endif // CLIENT_HPP
