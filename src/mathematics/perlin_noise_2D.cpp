#include "mathematics/perlin_noise_2D.hpp"
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>

PerlinNoise2D::PerlinNoise2D() {
    // Génération d'un vecteur de permutation avec 256 valeurs
    permutation.resize(256);
    std::iota(permutation.begin(), permutation.end(), 0);

    // Mélange du vecteur de permutation
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(permutation.begin(), permutation.end(), generator);

    // Duplique le vecteur de permutation
    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

float PerlinNoise2D::fade(float t) const {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise2D::lerp(float t, float a, float b) const {
    return a + t * (b - a);
}

float PerlinNoise2D::grad(int hash, float x, float y) const {
    int h = hash & 0xF;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise2D::sample(float x, float y) const {
    // Trouver la cellule de grille contenant le point
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;

    // Positions relatives dans la cellule
    x -= std::floor(x);
    y -= std::floor(y);

    // Calcul des courbes de lissage
    float u = fade(x);
    float v = fade(y);

    // Calcul des coins de la cellule
    int A = permutation[X] + Y;
    int B = permutation[X + 1] + Y;

    // Ajouter les résultats mélangés des 4 coins
    return lerp(v, lerp(u, grad(permutation[A], x, y),
                        grad(permutation[B], x - 1, y)),
                   lerp(u, grad(permutation[A + 1], x, y - 1),
                        grad(permutation[B + 1], x - 1, y - 1)));
}
