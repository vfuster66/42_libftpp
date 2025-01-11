#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

#include <cmath>
#include <stdexcept>
#include <iostream>

template <typename TType>
struct IVector2 {
    TType x; // Première coordonnée
    TType y; // Deuxième coordonnée

    // Constructeurs
    IVector2() : x(0), y(0) {}
    IVector2(TType x, TType y) : x(x), y(y) {}

    // Opérateurs
    IVector2 operator+(const IVector2& other) const {
        return {x + other.x, y + other.y};
    }

    IVector2 operator-(const IVector2& other) const {
        return {x - other.x, y - other.y};
    }

    IVector2 operator*(const IVector2& other) const {
        return {x * other.x, y * other.y};
    }

    IVector2 operator/(const IVector2& other) const {
        if (other.x == 0 || other.y == 0) {
            throw std::invalid_argument("Division by zero in vector.");
        }
        return {x / other.x, y / other.y};
    }

    bool operator==(const IVector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const IVector2& other) const {
        return !(*this == other);
    }

    // Méthodes supplémentaires
    float length() const {
        return std::sqrt(static_cast<float>(x * x + y * y));
    }

    IVector2<float> normalize() const {
        float len = length();
        if (len == 0) {
            throw std::invalid_argument("Cannot normalize a zero vector.");
        }
        return {static_cast<float>(x) / len, static_cast<float>(y) / len};
    }

    float dot(const IVector2& other) const {
        return static_cast<float>(x * other.x + y * other.y);
    }

    IVector2 cross() const {
        return {-y, x};
    }
};

// Surcharge pour affichage
template <typename TType>
std::ostream& operator<<(std::ostream& os, const IVector2<TType>& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

#endif // IVECTOR2_HPP
