//
// Created on 18/06/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_ZOMBIE_H
#define PROJECT_ZOMBIE_SHOOTER_ZOMBIE_H


#include <SFML/Graphics.hpp>

class Protagonist;
class Background;

const float DEFAULT_ZOMBIE_SPEED_WALKING = 220.0f;
const float DEFAULT_ZOMBIE_ATTACK_POWER = 10.0f;

class Zombie : public sf::Drawable{
public:
    Zombie(sf::Texture * texture, sf::Vector2f protagonistPosition, sf::Vector2i worldSize);
    ~Zombie() = default;
    void Hit(int damage);
    void Update(Protagonist &protagonist, sf::Time timeSinceLastUpdate);
    bool IsDead(){ return isDead; };

    void Move(const sf::Vector2f &offset);
    void Move(float offsetX, float offsetY);
    void SetPosition(const sf::Vector2f &position);
    sf::Vector2f GetPosition();
    void HandleCollisionWithBackground(const Background &background);


private:
    sf::Sprite sprite;
    sf::Texture * texture;
    float speed = DEFAULT_ZOMBIE_SPEED_WALKING;
    sf::Vector2f lastMovementChange;
    float lastRotation;
    float attackPower = DEFAULT_ZOMBIE_ATTACK_POWER;
    bool isDead = false;
    float timeSinceLastAttack = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    };
    bool intersects(const sf::CircleShape &circle, const sf::Vector2f &point);
};


#endif //PROJECT_ZOMBIE_SHOOTER_ZOMBIE_H
