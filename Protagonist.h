//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H
#define PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H


#include <SFML/Graphics.hpp>

const float DEFAULT_PROTAGONIST_SPEED_WALKING = 200.0f; // in pixels per second
const float DEFAULT_PROTAGONIST_SPEED_RUNNING = 350.0f; // in pixels per second

class Protagonist : public sf::Drawable {

public:
    Protagonist();
    ~Protagonist();
    sf::Vector2f GetPosition(){ return sprite.getPosition(); };
    void SetPosition(const sf::Vector2f & position);
    void Move(const sf::Vector2f & offset);
    void Move(float offsetX, float offsetY);
    void Update(const sf::Vector2f &mousePosition, const sf::Time &timeSinceLastUpdate);

private:
    void updateRotation(const sf::Vector2f &mousePosition);
    void handleMouse(const sf::Vector2f &mousePosition);
    void handleKeyboard(const sf::Time &timeSinceLastUpdate);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    };

    sf::Sprite sprite;
    sf::Texture texture;
    float speed = DEFAULT_PROTAGONIST_SPEED_WALKING;

};


#endif //PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H
