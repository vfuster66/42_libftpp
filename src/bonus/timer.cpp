#include "bonus/timer.hpp"

Timer::Timer() : duration(0), running(false) {}

void Timer::start(std::chrono::milliseconds duration) {
    this->duration = duration;
    startTime = std::chrono::steady_clock::now();
    running = true;
}

bool Timer::hasTimedOut() const {
    if (!running) return false;
    auto elapsedTime = std::chrono::steady_clock::now() - startTime;
    return elapsedTime >= duration;
}

void Timer::reset() {
    running = false;
}
