#ifndef RANDOM_2D_COORDINATE_GENERATOR_HPP
#define RANDOM_2D_COORDINATE_GENERATOR_HPP

#include <cstdint>

class Random2DCoordinateGenerator {
private:
    long long seedValue;

public:

    // Constructeur par défaut avec un seed constant
    Random2DCoordinateGenerator();

    // Retourne la valeur du seed
    long long seed() const;

    // Génère un nombre pseudo-aléatoire en fonction des coordonnées
    long long operator()(const long long& x, const long long& y) const;
};

#endif // RANDOM_2D_COORDINATE_GENERATOR_HPP
