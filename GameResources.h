//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H
#define PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H

#include "Protagonist.h"

class GameResources {
    GameResources();
    ~GameResources();
    Protagonist &protagonist;
public:
    Protagonist& newProtagonist();
};


#endif //PROJECT_ZOMBIE_SHOOTER_GAMERESOURCES_H
