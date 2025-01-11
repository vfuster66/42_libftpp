#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
private:

    // Point de départ du timer
    std::chrono::steady_clock::time_point startTime;

    // Durée pendant laquelle le timer est actif
    std::chrono::milliseconds duration;

    // Indique si le timer est actuellement en cours d'exécution
    bool running;

public:

    // Constructeur : initialise le timer comme non actif
    Timer();

    // Démarre le timer avec une durée donnée
    void start(std::chrono::milliseconds duration);

    // Vérifie si le timer a expiré
    bool hasTimedOut() const;

    // Réinitialise le timer
    void reset();
};

#endif // TIMER_HPP
