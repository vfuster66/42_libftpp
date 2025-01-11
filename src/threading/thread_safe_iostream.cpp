#include "threading/thread_safe_iostream.hpp"

// Déclaration d'un objet thread-local pour des entrées/sorties sécurisées
thread_local ThreadSafeIOStream threadSafeCout;

// Constructeur par défaut : Initialise le préfixe à une chaîne vide
ThreadSafeIOStream::ThreadSafeIOStream() : prefix_("") {}

// Définit un préfixe spécifique pour le flux de ce thread
void ThreadSafeIOStream::setPrefix(const std::string& prefix) {
    // Protège l'accès concurrent au préfixe avec un mutex
    std::lock_guard<std::mutex> lock(mtx_);
    // Met à jour le préfixe
    prefix_ = prefix;
}
