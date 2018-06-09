//
// Created on 01/05/2018.
//

#include "Background.h"
#include <iostream>

Background::Background() {
    const char * imagePath = "GameAssets_tmp/background.png";
    if (!texture.loadFromFile(imagePath))
        std::cout << "Failure when trying to load background image from " << imagePath << "!" << std::endl;
    else{
        background.setSize(sf::Vector2f(texture.getSize()));
        background.setTexture(&texture, false);
    }

}

Background::~Background() {

}

sf::Vector2f Background::GetSize() {
    return background.getSize();
}
