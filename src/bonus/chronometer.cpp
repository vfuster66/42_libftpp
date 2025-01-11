#include "bonus/chronometer.hpp"

// Initialisation du chronomètre avec un état non actif
Chronometer::Chronometer() : running(false) {}

// Démarre le chronomètre en enregistrant l'heure actuelle
void Chronometer::start() {
    startTime = std::chrono::steady_clock::now();
    running = true;
}

// Arrête le chronomètre en enregistrant l'heure actuelle comme temps de fin
void Chronometer::stop() {
    if (running) {
        endTime = std::chrono::steady_clock::now();
        running = false;
    }
}

// Réinitialise le chronomètre en mettant son état sur non actif
void Chronometer::reset() {
    running = false;
}

// Calcule le temps écoulé en secondes
// Si le chronomètre est actif, utilise l'heure actuelle comme temps de fin
double Chronometer::elapsedSeconds() const {
    auto end = running ? std::chrono::steady_clock::now() : endTime;
    std::chrono::duration<double> elapsed = end - startTime;
    return elapsed.count();
}

// Calcule le temps écoulé en millisecondes
// Si le chronomètre est actif, utilise l'heure actuelle comme temps de fin
double Chronometer::elapsedMilliseconds() const {
    auto end = running ? std::chrono::steady_clock::now() : endTime;
    std::chrono::duration<double, std::milli> elapsed = end - startTime;
    return elapsed.count();
}
