#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>
#include <iostream>

class Widget {
private:
    std::string name;

public:
    Widget(const std::string &name) : name(name) {}

    void draw() const {
        std::cout << "Drawing widget: " << name << std::endl;
    }

    void onClick() const {
        std::cout << "Widget " << name << " clicked!" << std::endl;
    }

    const std::string& getName() const {
        return name;
    }
};

#endif // WIDGET_HPP
