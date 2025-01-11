#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <memory>
#include "widget.hpp"

class Application {
private:
    std::vector<std::shared_ptr<Widget>> widgets;

public:
    void addWidget(const std::shared_ptr<Widget>& widget) {
        widgets.push_back(widget);
    }

    void drawAll() const {
        for (const auto &widget : widgets) {
            widget->draw();
        }
    }

    void clickWidget(const std::string &widgetName) const {
        for (const auto &widget : widgets) {
            if (widget->getName() == widgetName) {
                widget->onClick();
                return;
            }
        }
        std::cout << "No widget found with the name: " << widgetName << std::endl;
    }
};

#endif // APPLICATION_HPP
