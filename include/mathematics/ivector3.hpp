#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

#include <cmath>
#include <iostream>

// Template pour un vecteur 3D
template <typename TType>
struct IVector3 {
    TType x; // Première coordonnée
    TType y; // Deuxième coordonnée
    TType z; // Troisième coordonnée

    // Constructeur par défaut
    IVector3(TType x = 0, TType y = 0, TType z = 0) : x(x), y(y), z(z) {}

    // Opérateurs arithmétiques
    IVector3 operator+(const IVector3& other) const { return IVector3(x + other.x, y + other.y, z + other.z); }
    IVector3 operator-(const IVector3& other) const { return IVector3(x - other.x, y - other.y, z - other.z); }
    IVector3 operator*(const IVector3& other) const { return IVector3(x * other.x, y * other.y, z * other.z); }
    IVector3 operator/(const IVector3& other) const { return IVector3(x / other.x, y / other.y, z / other.z); }

    // Opérateurs de comparaison
    bool operator==(const IVector3& other) const { return x == other.x && y == other.y && z == other.z; }
    bool operator!=(const IVector3& other) const { return !(*this == other); }

    // Méthodes supplémentaires
    float length() const { return std::sqrt(static_cast<float>(x * x + y * y + z * z)); }

    IVector3<float> normalize() const {
        float len = length();
        return len == 0 ? IVector3<float>(0, 0, 0) : IVector3<float>(x / len, y / len, z / len);
    }

    float dot(const IVector3& other) const { return static_cast<float>(x * other.x + y * other.y + z * other.z); }

    IVector3 cross(const IVector3& other) const {
        return IVector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};

#endif // IVECTOR3_HPP
