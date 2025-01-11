#ifndef OBSERVABLE_VALUE_HPP
#define OBSERVABLE_VALUE_HPP

#include <vector>
#include <functional>

template <typename T>
class ObservableValue {
private:

    // La valeur surveillée
    T value;

    // Liste des fonctions d'observation
    std::vector<std::function<void(const T&)>> observers;

public:

    // Constructeur : initialise la valeur surveillée avec une valeur initiale
    ObservableValue(const T& initialValue);

    // Définit une nouvelle valeur, et notifie les observateurs si elle a changé
    void setValue(const T& newValue);

    // Retourne la valeur actuelle
    T getValue() const;

    // Ajoute un observateur qui sera notifié à chaque changement de valeur
    void subscribe(const std::function<void(const T&)>& observer);
};

// Implémentation du constructeur
template <typename T>
ObservableValue<T>::ObservableValue(const T& initialValue) : value(initialValue) {}

// Définit une nouvelle valeur et notifie les observateurs si la valeur a changé
template <typename T>
void ObservableValue<T>::setValue(const T& newValue) {

    // Vérifie si la nouvelle valeur est différente
    if (value != newValue) {

        // Met à jour la valeur
        value = newValue;

        // Notifie tous les observateurs
        for (const auto& observer : observers) {
            observer(value);
        }
    }
}

// Retourne la valeur actuelle
template <typename T>
T ObservableValue<T>::getValue() const {
    return value;
}

// Ajoute un observateur à la liste
template <typename T>
void ObservableValue<T>::subscribe(const std::function<void(const T&)>& observer) {
    observers.push_back(observer);
}

#endif // OBSERVABLE_VALUE_HPP
