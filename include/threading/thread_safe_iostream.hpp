#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <sstream>
#include <thread>

class ThreadSafeIOStream {
public:
    // Constructeur par défaut
    ThreadSafeIOStream();

    // Destructeur par défaut
    ~ThreadSafeIOStream() = default;

    // Définit un préfixe spécifique au thread pour chaque message
    void setPrefix(const std::string& prefix);

    // Surcharge de l'opérateur << pour permettre l'écriture dans le flux thread-safe
    template<typename T>
    ThreadSafeIOStream& operator<<(const T& value) {

        // Verrouille le mutex pour protéger l'accès concurrent
        std::lock_guard<std::mutex> lock(mtx_);

        // Stocke la valeur dans un buffer temporaire
        buffer_ << value;
        return *this;
    }

    // Surcharge de l'opérateur << pour gérer les manipulations comme std::endl
    ThreadSafeIOStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        
        // Verrouille le mutex pour protéger l'accès concurrent
        std::lock_guard<std::mutex> lock(mtx_);
        if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
            
            // Écrit le préfixe suivi du contenu du buffer dans le flux standard
            std::cout << prefix_ << buffer_.str() << std::endl;
            
            // Réinitialise le buffer après l'écriture
            buffer_.str("");
            buffer_.clear();
        }
        return *this;
    }

private:
    
    // Mutex pour protéger l'accès concurrent au flux
    std::mutex mtx_;

    // Buffer temporaire pour la construction des messages
    std::ostringstream buffer_;

    // Préfixe affiché avant chaque ligne de message
    std::string prefix_;
};

// Déclaration d'un flux thread-local pour une sortie thread-safe
extern thread_local ThreadSafeIOStream threadSafeCout;

#endif // THREAD_SAFE_IOSTREAM_HPP
