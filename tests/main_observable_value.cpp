#include <iostream>
#include "bonus/observable_value.hpp"

int main() {
    ObservableValue<int> observable(0);

    // Subscribe to value changes
    observable.subscribe([](const int& newValue) {
        std::cout << "Observer 1: Value changed to " << newValue << std::endl;
    });

    observable.subscribe([](const int& newValue) {
        std::cout << "Observer 2: Notified of new value: " << newValue << std::endl;
    });

    // Modify the value
    std::cout << "Setting value to 10..." << std::endl;
    observable.setValue(10);

    std::cout << "Setting value to 20..." << std::endl;
    observable.setValue(20);

    std::cout << "Setting value to 20 again (no change expected)..." << std::endl;
    observable.setValue(20);

    return 0;
}
