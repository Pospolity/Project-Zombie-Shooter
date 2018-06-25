//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H
#define PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H

#pragma once

#include <SFML/Graphics.hpp>

class Background;

const float DEFAULT_PROTAGONIST_SPEED_WALKING = 200.0f; // in pixels per second
const float DEFAULT_PROTAGONIST_SPEED_RUNNING = 350.0f; // in pixels per second
const int DEFAULT_PROTAGONIST_HP = 100;
const float RPS = 3.5f;

class Protagonist : public sf::Drawable {

public:

    enum class EQUIPED {NO_WEAPON, PISTOL, GUN};

    Protagonist();
    ~Protagonist();
    sf::Vector2f GetPosition() const { return sprite.getPosition(); };
    sf::FloatRect GetGlobalBound() { return sprite.getGlobalBounds(); };
    void SetPosition(const sf::Vector2f & position);
    void Move(const sf::Vector2f & offset);
    void Move(float offsetX, float offsetY);
    void Update(const sf::Vector2f &mousePosition, const sf::Time &timeSinceLastUpdate);
    void HandleCollisionWithBackground(const Background &background);
    void Attack(int damage) {this->hp -= damage; };
    int GetHP() const { return hp; };
    int GetMaxHP() const { return maxHP;};
    bool IsDead() const { return hp <= 0; };

private:
    EQUIPED equiped = EQUIPED::NO_WEAPON;
    void updateRotation(const sf::Vector2f &mousePosition);
    void handleMouse(const sf::Vector2f &mousePosition, const sf::Time &timeSinceLastUpdate);
    void handleKeyboard(const sf::Time &timeSinceLastUpdate);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    };

    int hp = DEFAULT_PROTAGONIST_HP;
    int maxHP = DEFAULT_PROTAGONIST_HP;
    sf::Sprite sprite;
    sf::Texture texture_no_weapon;
    sf::Texture texture_pistol;
    sf::Texture texture_gun;
    float timeSincePreviousFire = 0;

    float speed = DEFAULT_PROTAGONIST_SPEED_WALKING;
    sf::Vector2f lastMovementChange;
    float lastRotation;

};


#endif //PROJECT_ZOMBIE_SHOOTER_PROTAGONIST_H
