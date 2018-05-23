//
// Created on 04/05/2018.
//

#include <iostream>
#include "MapEditor.h"


MapEditor::MapEditor(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {
}

MapEditor::~MapEditor() {}

void MapEditor::init() {
    std::cout << "Map editor started!" << std::endl;

    goBackBtn.SetText("Go back", *(mainResources.defaultFont), 40);
    goBackBtn.SetSize(sf::Vector2f(250, 150));
    goBackBtn.SetFillColor(sf::Color::Red);
    goBackBtn.SetPosition(sf::Vector2f(25, 25));
}

void MapEditor::update() {

    sf::Vector2f mousePosition(sf::Mouse::getPosition(*(mainResources.window)));

    goBackBtn.Update(mousePosition);
    if (goBackBtn.IsActive())
        ShouldExit();
}

void MapEditor::draw() {

    mainResources.window->draw(goBackBtn);
}

