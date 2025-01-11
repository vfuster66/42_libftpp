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

    // Adresse du serveur
    std::string serverAddress;

    // Port du serveur
    size_t serverPort;

    // Actions associées aux types de message
    std::unordered_map<int, 
    std::function<void(const Message &)>> actions;

    // File des messages reçus
    std::queue<Message> receivedMessages;

    // Mutex pour protéger la file des messages
    std::mutex messageMutex;

    // Indique si le client est connecté               
    std::atomic<bool> connected = false;

    // Thread pour recevoir les messages
    std::thread receiveThread;

    // Méthode pour recevoir les messages en arrière-plan
    void receiveMessages();

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
