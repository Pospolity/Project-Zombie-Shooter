//
// Created on 01/05/2018.
//

#include "Protagonist.h"
#include <iostream>
#include <math.h>
#include "Collision.h"
#include "Background.h"

const float PI = 3.14159265f;

Protagonist::Protagonist() {

    const char * texturePathNoWeapon = "assets/graphics/protagonist_stand.png";
    const char * texturePathPistol = "assets/graphics/protagonist_pistol.png";
    const char * texturePathGun = "assets/graphics/protagonist_gun.png";
    if (!Collision::CreateTextureAndBitmask(texture_no_weapon, texturePathNoWeapon) ||
        !Collision::CreateTextureAndBitmask(texture_pistol, texturePathPistol) ||
        !Collision::CreateTextureAndBitmask(texture_gun, texturePathGun)){
        std::cout << "Failure when loading protagonist texture." << std::endl;
    } else {
        sprite.setTexture(texture_no_weapon);
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

    handleMouse(mousePosition, timeSinceLastUpdate);
    handleKeyboard(timeSinceLastUpdate);
}

void Protagonist::handleMouse(const sf::Vector2f &mousePosition, const sf::Time &timeSinceLastUpdate){
    updateRotation(mousePosition);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timeSincePreviousFire >= RPS){
        timeSincePreviousFire = 0;
    } else {
        timeSincePreviousFire += timeSinceLastUpdate.asSeconds();
    }
}

void Protagonist::updateRotation(const sf::Vector2f &mousePosition){
    sf::Vector2f spritePos = sprite.getPosition();
    sf::Vector2f diff = spritePos - mousePosition;
    float angle = atan2f(diff.y, diff.x) * 180 / PI;
    lastRotation = sprite.getRotation();
    sprite.setRotation(angle);
}

void Protagonist::handleKeyboard(const sf::Time &timeSinceLastUpdate) {

    sf::Vector2f movementChange(0, 0);

    speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) ? DEFAULT_PROTAGONIST_SPEED_RUNNING
                                                                    : DEFAULT_PROTAGONIST_SPEED_WALKING;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movementChange.y = (-1) * timeSinceLastUpdate.asSeconds() * speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movementChange.y = timeSinceLastUpdate.asSeconds() * speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movementChange.x = (-1) * timeSinceLastUpdate.asSeconds() * speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movementChange.x = timeSinceLastUpdate.asSeconds() * speed;

    this->Move(movementChange);
    lastMovementChange = movementChange;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
        if (equiped != EQUIPED::NO_WEAPON) {
            sprite.setTexture(texture_no_weapon, true);
            equiped = EQUIPED::NO_WEAPON;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
        if (equiped != EQUIPED::PISTOL) {
            sprite.setTexture(texture_pistol, true);
            equiped = EQUIPED::PISTOL;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
        if (equiped != EQUIPED::GUN) {
            sprite.setTexture(texture_gun, true);
            equiped = EQUIPED::GUN;
        }
    }
}

void Protagonist::HandleCollisionWithBackground(const Background &background) {
    std::vector<sf::Sprite> backgroundSprites = std::move(background.GetCollidingTileSprite(GetGlobalBound()));

    for (auto &bSprite : backgroundSprites){
        if(Collision::PixelPerfectTest(bSprite, this->sprite, 128)){
            this->Move(lastMovementChange.x * (-1), lastMovementChange.y * (-1));
            sprite.setRotation(lastRotation);
        }

    }
}


