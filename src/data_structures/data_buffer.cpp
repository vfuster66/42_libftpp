#include "data_structures/data_buffer.hpp"

// Sérialise un entier et l'ajoute au tampon
DataBuffer& DataBuffer::operator<<(const int& value) {
    write(reinterpret_cast<const char*>(&value), sizeof(value)); // Convertit l'entier en un tableau d'octets et l'écrit dans le tampon
    return *this;
}

// Désérialise un entier à partir du tampon
DataBuffer& DataBuffer::operator>>(int& value) {
    read(reinterpret_cast<char*>(&value), sizeof(value)); // Lit un entier du tampon et le reconvertit en entier
    return *this;
}

// Sérialise une chaîne de caractères et l'ajoute au tampon
DataBuffer& DataBuffer::operator<<(const std::string& value) {
    int size = static_cast<int>(value.size()); // Taille de la chaîne
    write(reinterpret_cast<const char*>(&size), sizeof(size)); // Écrit la taille de la chaîne en premier
    write(value.c_str(), size); // Écrit le contenu de la chaîne
    return *this;
}

// Désérialise une chaîne de caractères à partir du tampon
DataBuffer& DataBuffer::operator>>(std::string& value) {
    int size;
    read(reinterpret_cast<char*>(&size), sizeof(size)); // Lit la taille de la chaîne
    std::vector<char> temp(size); // Tampon temporaire pour stocker les caractères
    read(temp.data(), size); // Lit les caractères dans le tampon
    value.assign(temp.begin(), temp.end()); // Reconstruit la chaîne à partir du tampon temporaire
    return *this;
}

// Écrit un bloc de données brutes dans le tampon
void DataBuffer::write(const char* data, size_t size) {
    m_buffer.insert(m_buffer.end(), data, data + size); // Ajoute les octets à la fin du tampon
}

// Lit un bloc de données brutes à partir du tampon
void DataBuffer::read(char* data, size_t size) {
    // Vérifie si suffisamment de données sont disponibles dans le tampon
    if (m_readPosition + size > m_buffer.size()) {
        throw std::runtime_error("Buffer underflow"); // Génère une erreur si la lecture dépasse la taille disponible
    }
    
    // Copie les données demandées du tampon dans le tableau fourni
    std::copy(m_buffer.begin() + m_readPosition,
              m_buffer.begin() + m_readPosition + size,
              data);
    m_readPosition += size; // Met à jour la position de lecture
}
