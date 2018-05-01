//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_IGAMEOBJECT_H
#define PROJECT_ZOMBIE_SHOOTER_IGAMEOBJECT_H

#include "GameResources.h"

class IGameObject {
public:
    virtual void MakeAction(GameResources & gameResources) = 0;
    virtual void CheckCollision(int posX, int posY) = 0;
};


#endif //PROJECT_ZOMBIE_SHOOTER_IGAMEOBJECT_H
