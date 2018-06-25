//
// Created on 01/05/2018.
//

#include <iostream>
#include "GameResources.h"
#include "Collision.h"

const float SECONDS_TO_SPAWN_ZOMBIE = 5.0f;
const char * PATH_WITH_ZOMBIE_TEXTURE = "assets/graphics/zombie.png";

GameResources::GameResources() {
    if (!Collision::CreateTextureAndBitmask(zombieTexture, PATH_WITH_ZOMBIE_TEXTURE)) {
        std::cout << "Failure when loading zombie texture from file: " << PATH_WITH_ZOMBIE_TEXTURE << std::endl;
    }
}


Protagonist &GameResources::getProtagonist() {
    return protagonist;
}

Background &GameResources::getBackground() {
    return background;
}

void GameResources::SpawnZombieIfTimeHasCome(sf::Time timeSinceLastUpdate, sf::Vector2f protagonistPosition, sf::Vector2i worldSize) {
    if (zombies.size() < MAX_NUMBER_OF_ZOMBIES && timeSinceLastZombieSpawn >= SECONDS_TO_SPAWN_ZOMBIE){

        zombies.push_back(std::move(Zombie(&zombieTexture, protagonistPosition, worldSize)));

        timeSinceLastZombieSpawn = 0;
    } else {
        timeSinceLastZombieSpawn += timeSinceLastUpdate.asSeconds();
    }

}

std::vector<Zombie>& GameResources::getZombies() {
    return zombies;
}

