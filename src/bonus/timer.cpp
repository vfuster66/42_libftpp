#include "bonus/timer.hpp"

// Initialisation du Timer
// - `duration` est mis à 0, ce qui signifie qu'aucune durée n'est définie au départ
// - `running` est mis à false pour indiquer que le Timer n'est pas actif
Timer::Timer() : duration(0), running(false) {}

// Démarre le Timer avec une durée spécifique
// - `duration` est définie avec la valeur passée en paramètre
// - `startTime` capture l'heure actuelle comme point de départ
// - `running` est mis à true pour indiquer que le Timer est actif
void Timer::start(std::chrono::milliseconds duration) {
    this->duration = duration;
    startTime = std::chrono::steady_clock::now();
    running = true;
}

// Vérifie si le Timer a expiré
// - Si `running` est false, retourne false car le Timer n'est pas actif
// - Calcule le temps écoulé depuis `startTime`
// - Compare le temps écoulé à `duration` et retourne true si le Timer a expiré
bool Timer::hasTimedOut() const {
    if (!running) return false; // Timer inactif, donc pas de dépassement
    auto elapsedTime = std::chrono::steady_clock::now() - startTime;
    return elapsedTime >= duration; // Vérifie si la durée spécifiée est atteinte
}

// Réinitialise le Timer
// - Met `running` à false, arrêtant ainsi le Timer
// - `duration` et `startTime` ne sont pas réinitialisés ici
void Timer::reset() {
    running = false;
}
