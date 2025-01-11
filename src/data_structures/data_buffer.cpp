#include "data_structures/data_buffer.hpp"

DataBuffer& DataBuffer::operator<<(const int& value) {
    write(reinterpret_cast<const char*>(&value), sizeof(value));
    return *this;
}

DataBuffer& DataBuffer::operator>>(int& value) {
    read(reinterpret_cast<char*>(&value), sizeof(value));
    return *this;
}

DataBuffer& DataBuffer::operator<<(const std::string& value) {
    int size = static_cast<int>(value.size());
    write(reinterpret_cast<const char*>(&size), sizeof(size));
    write(value.c_str(), size);
    return *this;
}

DataBuffer& DataBuffer::operator>>(std::string& value) {
    int size;
    read(reinterpret_cast<char*>(&size), sizeof(size));
    
    std::vector<char> temp(size);
    read(temp.data(), size);
    value.assign(temp.begin(), temp.end());
    
    return *this;
}

void DataBuffer::write(const char* data, size_t size) {
    m_buffer.insert(m_buffer.end(), data, data + size);
}

void DataBuffer::read(char* data, size_t size) {
    if (m_readPosition + size > m_buffer.size()) {
        throw std::runtime_error("Buffer underflow");
    }
    
    std::copy(m_buffer.begin() + m_readPosition,
              m_buffer.begin() + m_readPosition + size,
              data);
    m_readPosition += size;
}