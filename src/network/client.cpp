// src/network/client.cpp
#include "network/client.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

// Constructeur
Client::Client() = default;

// Destructeur
Client::~Client()
{
    if (connected)
    {
        disconnect();
    }
}

// Se connecter au serveur
void Client::connect(const std::string &address, const size_t &port)
{
    if (connected)
    {
        throw std::runtime_error("Already connected to a server");
    }

    serverAddress = address;
    serverPort = port;

    // Simule la connexion
    connected = true;
    std::cout << "Connected to " << address << ":" << port << std::endl;

    // Lancer le thread pour recevoir les messages
    receiveThread = std::thread(&Client::receiveMessages, this);
}

// Se déconnecter du serveur
void Client::disconnect()
{
    if (!connected)
    {
        throw std::runtime_error("Not connected to a server");
    }

    connected = false;

    // Attendre que le thread de réception se termine
    if (receiveThread.joinable())
    {
        receiveThread.join();
    }

    std::cout << "Disconnected from server" << std::endl;
}

// Définir une action associée à un type de message
void Client::defineAction(const int &messageType, const std::function<void(const Message &msg)> &action)
{
    actions[messageType] = action;
}

// Envoyer un message au serveur
void Client::send(const Message &message)
{
    if (!connected)
    {
        throw std::runtime_error("Not connected to a server");
    }

    // Simule l'envoi du message
    std::cout << "Sent message of type " << message.type() << std::endl;
}

void Client::update()
{
    std::queue<Message> messagesToProcess;

    // Extraire les messages de la file sous un verrou
    {
        std::lock_guard<std::mutex> lock(messageMutex);
        std::swap(messagesToProcess, receivedMessages);
    }

    // Traiter chaque message
    while (!messagesToProcess.empty())
    {
        Message msg = std::move(messagesToProcess.front()); // Déplace le message hors de la file
        messagesToProcess.pop();

        auto it = actions.find(msg.type());
        if (it != actions.end())
        {
            it->second(msg);
        }
        else
        {
            std::cerr << "No action defined for message type " << msg.type() << std::endl;
        }
    }
}


// Recevoir les messages en arrière-plan (simulation)
void Client::receiveMessages()
{
    int messageCount = 0; // Limite pour le nombre de messages simulés

    while (connected && messageCount < 5) // Par exemple, maximum 5 messages
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Simule la réception d'un message
        Message msg(3);
        msg << 84; // Double d'une valeur fictive

        {
            std::lock_guard<std::mutex> lock(messageMutex);
            receivedMessages.push(std::move(msg));
        }

        std::cout << "Received message of type " << msg.type() << std::endl;

        ++messageCount;
    }
}


