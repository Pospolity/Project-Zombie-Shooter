//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H
#define PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H

#pragma once

#include "Protagonist.h"
#include "Background.h"
#include "Zombie.h"

const int MAX_NUMBER_OF_ZOMBIES = 10;

class GameResources {

public:
    GameResources();
    ~GameResources() = default;
    Protagonist& getProtagonist();
    Background& getBackground();
    std::vector<Zombie>& getZombies();
    void SpawnZombieIfTimeHasCome(sf::Time timeSinceLastUpdate, sf::Vector2f protagonistPosition, sf::Vector2i worldSize);

private:
    sf::Texture zombieTexture;
    std::vector<Zombie> zombies;
    float timeSinceLastZombieSpawn = 0;
    Background background;
    Protagonist protagonist;
};


#endif //PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H
