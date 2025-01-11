#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>

class Chronometer {
private:

    // Point de départ et d'arrêt du chronomètre
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

    // Indique si le chronomètre est en cours d'exécution
    bool running;

public:

    // Constructeur : initialise le chronomètre
    Chronometer();

    // Démarre le chronomètre
    void start();

    // Arrête le chronomètre
    void stop();

    // Réinitialise le chronomètre
    void reset();

    // Retourne vrai si le chronomètre est en cours d'exécution
    double elapsedSeconds() const;

    // Retourne le temps écoulé en secondes
    double elapsedMilliseconds() const;
};

#endif // CHRONOMETER_HPP
