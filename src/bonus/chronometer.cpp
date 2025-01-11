#include "bonus/chronometer.hpp"

Chronometer::Chronometer() : running(false) {}

void Chronometer::start() {
    startTime = std::chrono::steady_clock::now();
    running = true;
}

void Chronometer::stop() {
    if (running) {
        endTime = std::chrono::steady_clock::now();
        running = false;
    }
}

void Chronometer::reset() {
    running = false;
}

double Chronometer::elapsedSeconds() const {
    auto end = running ? std::chrono::steady_clock::now() : endTime;
    std::chrono::duration<double> elapsed = end - startTime;
    return elapsed.count();
}

double Chronometer::elapsedMilliseconds() const {
    auto end = running ? std::chrono::steady_clock::now() : endTime;
    std::chrono::duration<double, std::milli> elapsed = end - startTime;
    return elapsed.count();
}
