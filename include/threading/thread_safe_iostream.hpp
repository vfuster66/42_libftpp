#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <sstream>
#include <thread>

class ThreadSafeIOStream {
public:
    ThreadSafeIOStream();
    ~ThreadSafeIOStream() = default;

    // Définit un préfixe spécifique au thread
    void setPrefix(const std::string& prefix);

    // Surcharge de l'opérateur <<
    template<typename T>
    ThreadSafeIOStream& operator<<(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        buffer_ << value; // Stocke dans un buffer temporaire
        return *this;
    }

    // Gestion spécifique pour les manipulations comme std::endl
    ThreadSafeIOStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
            // Écrit le préfixe suivi du contenu du buffer
            std::cout << prefix_ << buffer_.str() << std::endl;
            buffer_.str(""); // Réinitialise le buffer
            buffer_.clear();
        }
        return *this;
    }

private:
    std::mutex mtx_;                // Verrou pour protéger les accès concurrents
    std::ostringstream buffer_;     // Buffer temporaire pour la construction des messages
    std::string prefix_;            // Préfixe de chaque ligne
};

// Déclaration d'un flux thread-local
extern thread_local ThreadSafeIOStream threadSafeCout;

#endif // THREAD_SAFE_IOSTREAM_HPP
