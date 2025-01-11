#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::milliseconds duration;
    bool running;

public:
    Timer();

    void start(std::chrono::milliseconds duration);
    bool hasTimedOut() const;
    void reset();
};

#endif // TIMER_HPP
