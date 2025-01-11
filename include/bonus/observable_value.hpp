#ifndef OBSERVABLE_VALUE_HPP
#define OBSERVABLE_VALUE_HPP

#include <vector>
#include <functional>

template <typename T>
class ObservableValue {
private:
    T value;
    std::vector<std::function<void(const T&)>> observers;

public:
    ObservableValue(const T& initialValue);

    void setValue(const T& newValue);
    T getValue() const;

    void subscribe(const std::function<void(const T&)>& observer);
};

template <typename T>
ObservableValue<T>::ObservableValue(const T& initialValue) : value(initialValue) {}

template <typename T>
void ObservableValue<T>::setValue(const T& newValue) {
    if (value != newValue) {
        value = newValue;
        for (const auto& observer : observers) {
            observer(value);
        }
    }
}

template <typename T>
T ObservableValue<T>::getValue() const {
    return value;
}

template <typename T>
void ObservableValue<T>::subscribe(const std::function<void(const T&)>& observer) {
    observers.push_back(observer);
}

#endif // OBSERVABLE_VALUE_HPP
