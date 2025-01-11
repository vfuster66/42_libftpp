#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>
#include <iostream>

class Widget {
private:

    // Nom du widget, utilisé pour l'identifier
    std::string name;

public:

    // Constructeur : initialise le widget avec un nom donné
    Widget(const std::string &name) : name(name) {}

    // Dessine le widget (affiche un message indiquant son nom)
    void draw() const {
        std::cout << "Drawing widget: " << name << std::endl;
    }

    // Réagit à un clic sur le widget (affiche un message indiquant son nom)
    void onClick() const {
        std::cout << "Widget " << name << " clicked!" << std::endl;
    }

    // Retourne le nom du widget
    const std::string& getName() const {
        return name;
    }
};

#endif // WIDGET_HPP
