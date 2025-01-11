#include "network/server.hpp"
#include "threading/thread_safe_iostream.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

// Constructeur
Server::Server() = default;

// Destructeur
Server::~Server()
{
    if (running)
    {
        stop();
    }
}

// Démarrer le serveur
void Server::start(const size_t &p_port)
{
    if (running)
    {
        throw std::runtime_error("Server is already running");
    }

    port = p_port;
    running = true;

    listenerThread = std::thread(&Server::listenForClients, this);
    threadSafeCout << "Server started on port " << port << std::endl;
}

// Arrêter le serveur
void Server::stop()
{
    running = false;

    if (listenerThread.joinable())
    {
        listenerThread.join();
    }

    threadSafeCout << "Server stopped" << std::endl;
}

// Définir une action associée à un type de message
void Server::defineAction(const int &messageType, const std::function<void(long long &, const Message &)> &action)
{
    actions[messageType] = action;
}

// Envoyer un message à un client spécifique
void Server::sendTo(const Message &message, long long clientID)
{
    if (clients.find(clientID) == clients.end())
    {
        throw std::runtime_error("Client not connected");
    }

    threadSafeCout << "Sent message of type " << message.type() << " to client " << clientID << std::endl;
}

// Mettre à jour : traiter les messages reçus
void Server::update()
{
    std::queue<std::pair<long long, Message>> messagesToProcess;

    {
        std::lock_guard<std::mutex> lock(messageMutex);
        std::swap(messagesToProcess, messages);
    }

    while (!messagesToProcess.empty())
    {
        auto [clientID, msg] = std::move(messagesToProcess.front());
        messagesToProcess.pop();

        auto it = actions.find(msg.type());
        if (it != actions.end())
        {
            it->second(clientID, msg);
        }
        else
        {
            threadSafeCout << "No action defined for message type " << msg.type() << std::endl;
        }
    }
}

// Écouter les connexions clientes
void Server::listenForClients()
{
    size_t maxClients = 5; // Nombre maximum de clients
    bool limitReachedLogged = false; // Flag pour éviter les logs répétés

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Vérifier si le nombre maximal de clients est atteint
        {
            std::lock_guard<std::mutex> lock(messageMutex);
            if (clients.size() >= maxClients)
            {
                if (!limitReachedLogged)
                {
                    threadSafeCout << "Max client limit reached (" << maxClients << "). Rejecting new connections." << std::endl;
                    limitReachedLogged = true; // Log uniquement une fois
                }
                continue;
            }
            limitReachedLogged = false; // Réinitialiser le flag si une place est libérée
        }

        // Simuler une nouvelle connexion client
        static long long clientID = 1;

        {
            std::lock_guard<std::mutex> lock(messageMutex);
            clients[clientID] = 1;
        }

        threadSafeCout << "Client " << clientID << " connected" << std::endl;

        // Simuler l'envoi d'un message du client
        Message msg(1);
        msg << 42;

        {
            std::lock_guard<std::mutex> lock(messageMutex);
            messages.emplace(clientID, std::move(msg));
        }

        clientID++;
    }
}


