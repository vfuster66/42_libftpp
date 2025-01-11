#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <vector>
#include <string>
#include <stdexcept>

class DataBuffer {
public:

    // Constructeur par défaut
    DataBuffer() = default;

    // Destructeur par défaut
    ~DataBuffer() = default;

    // Surcharge de l'opérateur << pour ajouter un entier au buffer
    DataBuffer& operator<<(const int& value);

    // Surcharge de l'opérateur >> pour lire un entier à partir du buffer
    DataBuffer& operator>>(int& value);
    
    // Surcharge de l'opérateur << pour ajouter une chaîne de caractères au buffer
    DataBuffer& operator<<(const std::string& value);

    // Surcharge de l'opérateur >> pour lire une chaîne de caractères à partir du buffer
    DataBuffer& operator>>(std::string& value);

private:

    // Contient les données sérialisées
    std::vector<char> m_buffer;

    // Position de lecture dans le buffer
    size_t m_readPosition = 0;

    // Méthode utilitaire pour écrire des données brutes dans le buffer
    void write(const char* data, size_t size);

    // Méthode utilitaire pour lire des données brutes du buffer
    void read(char* data, size_t size);
};

#endif