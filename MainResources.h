//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAINRESOURCES_H
#define PROJECT_ZOMBIE_SHOOTER_MAINRESOURCES_H

#include <SFML/Graphics.hpp>


struct MainResources {
    sf::RenderWindow * window;
    sf::Font * defaultFont; // clear and readable font for majority of texts in game
    sf::Font * specialFont; // more fancy font for e.g. text in buttons, logo
};



#endif //PROJECT_ZOMBIE_SHOOTER_MAINRESOURCES_H
