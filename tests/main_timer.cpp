#include <iostream>
#include <thread>
#include "bonus/timer.hpp"

int main() {
    Timer timer;

    std::cout << "Starting a timer for 2 seconds..." << std::endl;
    timer.start(std::chrono::seconds(2));

    while (!timer.hasTimedOut()) {
        std::cout << "Waiting for the timer to time out..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Timer has timed out!" << std::endl;

    return 0;
}
