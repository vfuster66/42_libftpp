#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:

    // Différents niveaux de log
    enum Level {
        INFO,
        WARNING,
        ERROR
    };

private:

    // Niveau de log actuel pour filtrer les messages
    Level currentLevel;

    // Retourne l'horodatage actuel au format "YYYY-MM-DD HH:MM:SS"
    std::string getTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};
        localtime_r(&time, &localTime);

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    // Convertit le niveau de log en chaîne de caractères
    std::string levelToString(Level level) const {
        switch (level) {
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

public:

    // Constructeur : initialise le niveau de log par défaut à INFO
    Logger() : currentLevel(INFO) {}

    // Définit le niveau minimum à afficher
    void setLevel(Level level) {
        currentLevel = level;
    }

    // Enregistre un message avec un niveau donné
    void log(Level level, const std::string &message) const {
        if (level >= currentLevel) {
            std::cout << "[" << getTimestamp() << "] [" << levelToString(level) << "] " << message << std::endl;
        }
    }

    // Méthodes de commodité pour chaque niveau de log
    void info(const std::string &message) const {
        log(INFO, message);
    }

    void warning(const std::string &message) const {
        log(WARNING, message);
    }

    void error(const std::string &message) const {
        log(ERROR, message);
    }
};

#endif // LOGGER_HPP
