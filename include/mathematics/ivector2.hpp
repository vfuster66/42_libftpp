#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

#include <cmath>
#include <stdexcept>
#include <iostream>

template <typename TType>
struct IVector2 {

    // Première coordonnée
    TType x;

    // Deuxième coordonnée
    TType y;

    // Constructeurs

    // Par défaut, initialise le vecteur à (0, 0)
    IVector2() : x(0), y(0) {}
    
     // Initialise le vecteur avec des coordonnées spécifiques
    IVector2(TType x, TType y) : x(x), y(y) {}

    // Opérateurs arithmétiques
    IVector2 operator+(const IVector2& other) const {

        // Additionne les composantes des deux vecteurs
        return {x + other.x, y + other.y};
    }

    IVector2 operator-(const IVector2& other) const {

        // Soustrait les composantes des deux vecteurs
        return {x - other.x, y - other.y};
    }

    IVector2 operator*(const IVector2& other) const {

        // Multiplie les composantes des deux vecteurs
        return {x * other.x, y * other.y};
    }

    IVector2 operator/(const IVector2& other) const {

        // Divise les composantes des deux vecteurs, vérifie la division par zéro
        if (other.x == 0 || other.y == 0) {
            throw std::invalid_argument("Division by zero in vector.");
        }
        return {x / other.x, y / other.y};
    }

    // Opérateurs de comparaison
    bool operator==(const IVector2& other) const {

        // Vérifie si les deux vecteurs sont égaux (composantes identiques)
        return x == other.x && y == other.y;
    }

    bool operator!=(const IVector2& other) const {

        // Vérifie si les deux vecteurs sont différents
        return !(*this == other);
    }

    // Méthodes supplémentaires

    float length() const {

        // Retourne la longueur du vecteur (norme euclidienne)
        return std::sqrt(static_cast<float>(x * x + y * y));
    }

    IVector2<float> normalize() const {

        // Retourne un vecteur normalisé (longueur égale à 1)
        float len = length();
        if (len == 0) {
            throw std::invalid_argument("Cannot normalize a zero vector.");
        }
        return {static_cast<float>(x) / len, static_cast<float>(y) / len};
    }

    float dot(const IVector2& other) const {

        // Produit scalaire des deux vecteurs
        return static_cast<float>(x * other.x + y * other.y);
    }

    IVector2 cross() const {

        // Produit vectoriel en 2D (orthogonal au vecteur courant)
        return {-y, x};
    }
};

// Surcharge de l'opérateur << pour afficher un vecteur
template <typename TType>
std::ostream& operator<<(std::ostream& os, const IVector2<TType>& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

#endif // IVECTOR2_HPP
