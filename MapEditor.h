//
// Created on 05/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
#define PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H

#include <SFML/Window.hpp>

class MapEditor {
    bool isOpen = false;
    sf::Window &window;

public:
    MapEditor(sf::Window & window);
    MapEditor(sf::Window &&) = delete; // prevents rvalue binding
    ~MapEditor();

    void Start();
};

#endif //PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
