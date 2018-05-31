//
// Created on 04/05/2018.
//

#include <iostream>
#include "MapEditor.h"

/* TODO: move to some examples class
 * void helloWorld() {
    std::cout << "Helo" << std::endl;
}
void saySth(const char * textToSay) {
    std::cout << textToSay << std::endl;
}*/

MapEditor::MapEditor(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {}

MapEditor::~MapEditor() {}

void MapEditor::init() {

    goBackBtn.SetText("Go back", *(mainResources.defaultFont), 40);
    goBackBtn.SetSize(sf::Vector2f(250, 150));
    goBackBtn.SetFillColor(sf::Color::Red);
    goBackBtn.SetPosition(sf::Vector2f(25, 25));


    /* TODO: move to some examples class
     * std::function<void()> onReleased = helloWorld;
    std::function<void()> onReleased2 = [](){ saySth("I am saying something!"); };
    std::function<void()> onReleased3 = std::bind(saySth, "Hello my friend.");
     */

    buttonTriggerFunction onReleased = std::bind(&MapEditor::ShouldExit, this);
    goBackBtn.OnReleasedTriggerFunction(onReleased);

    // TODO: move to some examples class
    //goBackBtn.OnReleasedTriggerFunction(onReleased);
    //goBackBtn.OnReleasedTriggerFunction(onReleased2);
    //goBackBtn.OnReleasedTriggerFunction(onReleased3);
}

void MapEditor::update() {

    sf::Vector2f mousePosition(sf::Mouse::getPosition(*(mainResources.window)));

    if (this->IsFocused())
        goBackBtn.Update(mousePosition);
}

void MapEditor::draw() {

    mainResources.window->draw(goBackBtn);
}

