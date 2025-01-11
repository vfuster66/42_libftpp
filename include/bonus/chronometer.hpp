#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>

class Chronometer {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;
    bool running;

public:
    Chronometer();

    void start();
    void stop();
    void reset();
    double elapsedSeconds() const; // Retourne le temps écoulé en secondes
    double elapsedMilliseconds() const; // Retourne le temps écoulé en millisecondes
};

#endif // CHRONOMETER_HPP
