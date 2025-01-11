#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <memory>
#include "widget.hpp"

// Classe Application : Représente une application contenant des widgets.
class Application {
private:
    // Liste des widgets de l'application, chaque widget est géré via un std::shared_ptr
    std::vector<std::shared_ptr<Widget>> widgets;

public:
    // Ajoute un widget à la liste des widgets
    void addWidget(const std::shared_ptr<Widget>& widget) {
        widgets.push_back(widget);
    }

    // Appelle la méthode draw() de tous les widgets pour les dessiner
    void drawAll() const {
        for (const auto &widget : widgets) {
            widget->draw();  // Appelle la méthode spécifique à chaque widget
        }
    }

    // Permet de cliquer sur un widget en recherchant son nom
    void clickWidget(const std::string &widgetName) const {
        for (const auto &widget : widgets) {
            if (widget->getName() == widgetName) {  // Vérifie si le nom correspond
                widget->onClick();  // Appelle l'action associée au clic
                return;  // Quitte la boucle après avoir trouvé le widget
            }
        }
        // Message si aucun widget avec le nom donné n'est trouvé
        std::cout << "No widget found with the name: " << widgetName << std::endl;
    }
};

#endif // APPLICATION_HPP
