//
// Created on 01/05/2018.
//

#include "Protagonist.h"
#include <iostream>
#include <math.h>

const float PI = 3.14159265f;

Protagonist::Protagonist() {

    const char * texturePath = "assets/graphics/protagonist_stand.png";
    if (!texture.loadFromFile(texturePath)){
        std::cout << "Failure when loading protagonist texture from file: " << texturePath << std::endl;
    } else {
        sprite.setTexture(texture);
        sf::FloatRect spriteBounds = sprite.getLocalBounds();
        sprite.setOrigin(spriteBounds.left + spriteBounds.width / 2.0f , spriteBounds.top + spriteBounds.height / 2.0f);
    }
}

Protagonist::~Protagonist() {

}

void Protagonist::Move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Protagonist::Move(const sf::Vector2f &offset) {
    sprite.move(offset);
}

void Protagonist::SetPosition(const sf::Vector2f &position) {
    sprite.setPosition(position);
}

void Protagonist::Update(const sf::Vector2f &mousePosition, const sf::Time &timeSinceLastUpdate) {

    handleMouse(mousePosition);
    handleKeyboard(timeSinceLastUpdate);

}
void Protagonist::handleMouse(const sf::Vector2f &mousePosition){
    updateRotation(mousePosition);
}

void Protagonist::updateRotation(const sf::Vector2f &mousePosition){
    sf::Vector2f spritePos = sprite.getPosition();
    sf::Vector2f diff = spritePos - mousePosition;
    float angle = atan2f(diff.y, diff.x) * 180 / PI;
    sprite.setRotation(angle);
}

void Protagonist::handleKeyboard(const sf::Time &timeSinceLastUpdate) {

    sf::Vector2f movementChange(0, 0);

    speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) ? DEFAULT_PROTAGONIST_SPEED_RUNNING : DEFAULT_PROTAGONIST_SPEED_WALKING;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movementChange.y = (-1) * timeSinceLastUpdate.asSeconds() * speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movementChange.y = timeSinceLastUpdate.asSeconds() * speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movementChange.x = (-1) * timeSinceLastUpdate.asSeconds() * speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movementChange.x = timeSinceLastUpdate.asSeconds() * speed;

    this->Move(movementChange);
}

