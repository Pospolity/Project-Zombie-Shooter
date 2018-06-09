//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H
#define PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H


#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {

public:
    Background();
    ~Background();
    sf::Vector2f GetSize();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(background, states);
    };

    sf::Texture texture;
    sf::RectangleShape background;

};


#endif //PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H
