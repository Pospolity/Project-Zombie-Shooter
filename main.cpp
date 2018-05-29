//
// Created on 17/04/2018.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include "UI_Button.h"
#include "MainResources.h"
#include <iostream>
#include <string>


int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Hello SFML");

    sf::Font font;
    font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

    MainResources mainResources{
        &window,
        &font
    };

    MainMenu(mainResources).Start();

    return 0;
}

