#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP

#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

class PerlinNoise2D {
private:
    std::vector<int> permutation;

    // Fonction de lissage (fade)
    float fade(float t) const;

    // Interpolation linéaire (lerp)
    float lerp(float t, float a, float b) const;

    // Calcul du gradient
    float grad(int hash, float x, float y) const; 

public:

    // Constructeur par défaut
    PerlinNoise2D();

    // Échantillonnage du bruit de Perlin
    float sample(float x, float y) const;
};

#endif // PERLIN_NOISE_2D_HPP
