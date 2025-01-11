#include "network/message.hpp"
#include <iostream>
#include <string>

int main()
{
    // Créer un message de type 1
    Message msg(1);

    // Ajouter des données dans le message
    msg << "Hello, " << "world! " << 42;

    // Afficher le contenu brut du message
    std::cout << "Raw content: " << msg.rawContent() << std::endl;

    // Lire les données depuis le message
    std::string part1, part2;
    int number;
    msg >> part1 >> part2 >> number;

    std::cout << "Extracted: " << part1 << part2 << number << std::endl;

    // Afficher le type du message
    std::cout << "Message type: " << msg.type() << std::endl;

    return 0;
}
