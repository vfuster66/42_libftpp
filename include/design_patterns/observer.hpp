#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <functional>
#include <map>
#include <vector>

template<typename TEvent>
class Observer {
public:
    // Définition du type de callback
    using Callback = std::function<void()>;

    // Souscrire à un événement
    void subscribe(const TEvent& event, const Callback& lambda) {
        m_subscribers[event].push_back(lambda);
    }

    // Notifier tous les souscripteurs d'un événement
    void notify(const TEvent& event) {

        // Vérifie si l'événement a des souscripteurs
        auto it = m_subscribers.find(event);
        if (it != m_subscribers.end()) {

            // Exécute tous les callbacks associés à cet événement
            for (const auto& callback : it->second) {
                callback();
            }
        }
    }

private:

    // Map qui associe chaque événement à un vecteur de callbacks
    std::map<TEvent, std::vector<Callback>> m_subscribers;
};

#endif