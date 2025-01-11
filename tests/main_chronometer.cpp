#include <iostream>
#include <thread>
#include "bonus/chronometer.hpp"

int main() {
    Chronometer chronometer;

    std::cout << "Starting the chronometer..." << std::endl;
    chronometer.start();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    chronometer.stop();
    std::cout << "Chronometer stopped." << std::endl;

    std::cout << "Elapsed time: " << chronometer.elapsedSeconds() << " seconds." << std::endl;
    std::cout << "Elapsed time: " << chronometer.elapsedMilliseconds() << " milliseconds." << std::endl;

    chronometer.reset();
    std::cout << "Chronometer reset." << std::endl;

    return 0;
}
