#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

#include <cmath>
#include <iostream>

// Template pour un vecteur 3D
template <typename TType>
struct IVector3 {
    // Première coordonnée
    TType x;

    // Deuxième coordonnée
    TType y;

    // Troisième coordonnée
    TType z;

    // Constructeur par défaut
    IVector3(TType x = 0, TType y = 0, TType z = 0) : x(x), y(y), z(z) {}

    // Opérateurs arithmétiques

    // Additionne les composantes de deux vecteurs
    IVector3 operator+(const IVector3& other) const { 
        return IVector3(x + other.x, y + other.y, z + other.z); 
    }

    // Soustrait les composantes de deux vecteurs
    IVector3 operator-(const IVector3& other) const { 
        return IVector3(x - other.x, y - other.y, z - other.z); 
    }

    // Multiplie les composantes de deux vecteurs
    IVector3 operator*(const IVector3& other) const { 
        return IVector3(x * other.x, y * other.y, z * other.z); 
    }

    // Divise les composantes de deux vecteurs (attention aux divisions par zéro)
    IVector3 operator/(const IVector3& other) const { 
        return IVector3(x / other.x, y / other.y, z / other.z); 
    }

    // Opérateurs de comparaison

    // Vérifie si les vecteurs sont identiques (mêmes composantes)
    bool operator==(const IVector3& other) const { 
        return x == other.x && y == other.y && z == other.z; 
    }

    // Vérifie si les vecteurs sont différents
    bool operator!=(const IVector3& other) const { 
        return !(*this == other); 
    }

    // Méthodes supplémentaires

    // Calcule la norme du vecteur (distance à l'origine)
    float length() const { 
        return std::sqrt(static_cast<float>(x * x + y * y + z * z)); 
    }

    // Retourne un vecteur unitaire avec la même direction (norme égale à 1)
    IVector3<float> normalize() const {
        float len = length();
        return len == 0 ? IVector3<float>(0, 0, 0) : IVector3<float>(x / len, y / len, z / len);
    }

    // Produit scalaire : mesure la projection d'un vecteur sur un autre
    float dot(const IVector3& other) const { 
        return static_cast<float>(x * other.x + y * other.y + z * other.z); 
    }

    // Produit vectoriel : retourne un vecteur perpendiculaire aux deux vecteurs donnés
    IVector3 cross(const IVector3& other) const {
        return IVector3(

            // Composante x
            y * other.z - z * other.y,

            // Composante y
            z * other.x - x * other.z,

            // Composante z
            x * other.y - y * other.x
        );
    }
};

#endif // IVECTOR3_HPP
