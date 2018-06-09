//
// Created on 17/04/2018.
//

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "UI_Button.h"
#include "MainResources.h"
#include <iostream>
#include <string>


int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Zombie Shooter", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Font defaultFont;
    sf::Font specialFont;
    defaultFont.loadFromFile("assets/fonts/OpenSans-Bold.ttf");
    specialFont.loadFromFile("assets/fonts/MeltdownMF.ttf");
    MainResources mainResources{
        &window,
        &defaultFont,
        &specialFont
    };

    MainMenu(mainResources).Start();

    return 0;
}

