#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <sstream>

class Message
{
private:
    int messageType;             // Type du message
    std::stringstream buffer;    // Contenu du message stocké sous forme de flux

public:
    // Constructeur prenant un type de message en paramètre
    explicit Message(int type);

    Message() : messageType(0) {}

    // Constructeur de déplacement
    Message(Message &&other) noexcept;

    // Opérateur de déplacement
    Message &operator=(Message &&other) noexcept;

    // Suppression du constructeur de copie
    Message(const Message &) = delete;
    Message &operator=(const Message &) = delete;

    // Retourne le type du message
    int type() const;

    // Opérateur << pour ajouter des données dans le message
    template <typename T>
    Message &operator<<(const T &data);

    // Opérateur >> pour extraire des données du message
    template <typename T>
    Message &operator>>(T &data) const;

    // Pour afficher le contenu brut du message (utile pour le debug)
    std::string rawContent() const;
};

// Implémentation des méthodes inline

// Constructeur
inline Message::Message(int type) : messageType(type) {}

// Constructeur de déplacement
inline Message::Message(Message &&other) noexcept
    : messageType(other.messageType), buffer(std::move(other.buffer)) {}

// Opérateur de déplacement
inline Message &Message::operator=(Message &&other) noexcept
{
    if (this != &other)
    {
        messageType = other.messageType;
        buffer = std::move(other.buffer);
    }
    return *this;
}

// Retourne le type du message
inline int Message::type() const
{
    return messageType;
}

// Opérateur << : Ajoute des données au message
template <typename T>
Message &Message::operator<<(const T &data)
{
    buffer << data; // Ajoute les données dans le flux interne
    return *this;
}

// Opérateur >> : Extrait des données du message
template <typename T>
Message &Message::operator>>(T &data) const
{
    const_cast<std::stringstream &>(buffer) >> data; // Lit les données depuis le flux interne
    return const_cast<Message &>(*this);
}

// Retourne le contenu brut du message pour le debug
inline std::string Message::rawContent() const
{
    return buffer.str();
}

#endif // MESSAGE_HPP
