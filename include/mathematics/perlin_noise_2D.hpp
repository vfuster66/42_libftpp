#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP

#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

class PerlinNoise2D {
private:
    std::vector<int> permutation;

    float fade(float t) const; // Fonction de lissage (fade)
    float lerp(float t, float a, float b) const; // Interpolation linéaire (lerp)
    float grad(int hash, float x, float y) const; // Calcul du gradient

public:
    PerlinNoise2D(); // Constructeur

    float sample(float x, float y) const; // Échantillonnage du bruit de Perlin
};

#endif // PERLIN_NOISE_2D_HPP
