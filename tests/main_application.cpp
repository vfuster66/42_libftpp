#include "bonus/widget.hpp"
#include "bonus/application.hpp"

int main() {
    Application app;

    auto button = std::make_shared<Widget>("Button");
    auto label = std::make_shared<Widget>("Label");
    auto textField = std::make_shared<Widget>("TextField");

    app.addWidget(button);
    app.addWidget(label);
    app.addWidget(textField);

    std::cout << "Drawing all widgets in the application:" << std::endl;
    app.drawAll();

    std::cout << "\nSimulating clicks on widgets:" << std::endl;
    app.clickWidget("Button");   // Expected: Widget Button clicked!
    app.clickWidget("TextField"); // Expected: Widget TextField clicked!
    app.clickWidget("Unknown"); // Expected: No widget found with the name: Unknown

    return 0;
}
