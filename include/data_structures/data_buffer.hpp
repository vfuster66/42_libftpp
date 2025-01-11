#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <vector>
#include <string>
#include <stdexcept>

class DataBuffer {
public:
    DataBuffer() = default;
    ~DataBuffer() = default;

    // Opérateurs de base pour les types primitifs
    DataBuffer& operator<<(const int& value);
    DataBuffer& operator>>(int& value);
    
    DataBuffer& operator<<(const std::string& value);
    DataBuffer& operator>>(std::string& value);

private:
    std::vector<char> m_buffer;
    size_t m_readPosition = 0;

    // Méthodes utilitaires pour la sérialisation
    void write(const char* data, size_t size);
    void read(char* data, size_t size);
};

#endif