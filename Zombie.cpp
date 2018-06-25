//
// Created on 18/06/2018.
//

#include "Zombie.h"
#include "Collision.h"
#include "Protagonist.h"
#include "Background.h"
#include <math.h>
#include <iostream>

const float PI = 3.14159265f;

const float RANGE_OF_ZOMBIE_ATTACK = 50.0f;
const float RANGE_OF_ZOMBIE_SENSE = 600.0f;
const float AREA_OF_ZOMBIES_NOT_SPAWN = 550.0f;
const float FREQUENCY_OF_ZOMBIES_ATTACK = 1.5f; // in seconds


Zombie::Zombie(sf::Texture * texture, sf::Vector2f protagonistPosition, sf::Vector2i worldSize) {
    srand(time(NULL));
    do {
        sprite.setPosition(rand() % worldSize.x, rand() % worldSize.y);
    } while (intersects(sf::CircleShape(AREA_OF_ZOMBIES_NOT_SPAWN), protagonistPosition));

    sprite.setTexture(*texture);
    sprite.setOrigin((sprite.getLocalBounds().left + sprite.getLocalBounds().width) / 2.0f, (sprite.getLocalBounds().top + sprite.getLocalBounds().height) / 2.0f);
}

void Zombie::Move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Zombie::Move(const sf::Vector2f &offset) {
    sprite.move(offset);
}

void Zombie::SetPosition(const sf::Vector2f &position) {
    sprite.setPosition(position);
}

sf::Vector2f Zombie::GetPosition() {
    return sprite.getPosition();
}

void Zombie::Update(Protagonist &protagonist, sf::Time timeSinceLastUpdate) {
    sf::Vector2f spritePos = sprite.getPosition();
    sf::Vector2f diff = spritePos - protagonist.GetPosition();
    float angle = atan2f(diff.y, diff.x);
    float angleToRotate = angle * 180 / PI;
    lastRotation = sprite.getRotation();
    sprite.setRotation(angleToRotate - 180);

    sf::CircleShape rangeOfZombieSense(RANGE_OF_ZOMBIE_SENSE);
    sf::FloatRect bounds = rangeOfZombieSense.getLocalBounds();
    rangeOfZombieSense.setOrigin((bounds.left + bounds.width) / 2.0f, (bounds.top + bounds.height) / 2.0f);
    rangeOfZombieSense.setPosition(GetPosition());
    if (intersects(rangeOfZombieSense, protagonist.GetPosition())){
        sf::Vector2f movementChange(timeSinceLastUpdate.asSeconds() * speed * (-1) * cos(angle), timeSinceLastUpdate.asSeconds() * speed * (-1) * sin(angle));
        Move(movementChange);
        lastMovementChange = movementChange;
    }

    sf::CircleShape rangeOfZombieAttack(RANGE_OF_ZOMBIE_ATTACK);
    bounds = rangeOfZombieAttack.getLocalBounds();
    rangeOfZombieAttack.setOrigin((bounds.left + bounds.width) / 2.0f, (bounds.top + bounds.height) / 2.0f);
    rangeOfZombieAttack.setPosition(GetPosition());
    if(intersects(rangeOfZombieAttack, protagonist.GetPosition()) && timeSinceLastAttack > FREQUENCY_OF_ZOMBIES_ATTACK){
        protagonist.Attack(attackPower);
        timeSinceLastAttack = 0;
    }
    else
        timeSinceLastAttack += timeSinceLastUpdate.asSeconds();
}

bool Zombie::intersects(const sf::CircleShape &circle, const sf::Vector2f &point)
{
    sf::Vector2f circleDistance;
    circleDistance.x = abs(circle.getPosition().x - point.x);
    circleDistance.y = abs(circle.getPosition().y - point.y);

    if (circleDistance.x >  circle.getRadius()) { return false; }
    if (circleDistance.y >  circle.getRadius()) { return false; }

    if (circleDistance.x <= 1) { return true; }
    if (circleDistance.y <= 1) { return true; }

    float cornerDistance_sq = pow(circleDistance.x, 2) + pow(circleDistance.y, 2);

    return (cornerDistance_sq <= pow(circle.getRadius(), 2));
}

void Zombie::HandleCollisionWithBackground(const Background &background) {
    std::vector<sf::Sprite> backgroundSprites = std::move(background.GetCollidingTileSprite(sprite.getGlobalBounds()));

    for (auto &bSprite : backgroundSprites){
        if(Collision::PixelPerfectTest(bSprite, this->sprite, 128)){
            this->Move(lastMovementChange.x * (-1), lastMovementChange.y * (-1));
            sprite.setRotation(lastRotation);
        }
    }
}
