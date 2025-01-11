#include "mathematics/random_2D_coordinate_generator.hpp"

// Constructeur qui initialise le seed
Random2DCoordinateGenerator::Random2DCoordinateGenerator()
    : seedValue(0xABCDEF1234567890) // Un seed constant
{}

// Retourne la valeur du seed
long long Random2DCoordinateGenerator::seed() const {
    return seedValue;
}

// Génère un nombre pseudo-aléatoire basé sur les coordonnées
long long Random2DCoordinateGenerator::operator()(const long long& x, const long long& y) const {
    long long hash = seedValue;

    // Combinaison unique des coordonnées
    hash ^= x + 0x9E3779B9 + (hash << 6) + (hash >> 2);
    hash ^= y + 0x9E3779B9 + (hash << 6) + (hash >> 2);

    return hash;
}
