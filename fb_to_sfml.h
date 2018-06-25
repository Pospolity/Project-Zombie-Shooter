//
// Created on 17/06/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_FB_TO_SFML_CPP_H
#define PROJECT_ZOMBIE_SHOOTER_FB_TO_SFML_CPP_H

#include <SFML/Graphics.hpp>
#include "map_generated.h"
#include "flatbuffers/flatbuffers.h"

inline sf::Vector2i Vec2iToVector2i(const tileMap::Vec2i & vec2i){
    return sf::Vector2i(vec2i.x(), vec2i.y());
}

inline sf::Vector2f Vec2fToVector2f(const tileMap::Vec2f & vec2f){
    return sf::Vector2f(vec2f.x(), vec2f.y());
}

inline tileMap::Vec2i Vector2iToVec2i(const sf::Vector2i & vector2i){
    return tileMap::Vec2i(vector2i.x, vector2i.y);
}

inline tileMap::Vec2f Vector2fToVec2f(const sf::Vector2f & vector2f){
    return tileMap::Vec2f(vector2f.x, vector2f.y);
}


#endif //PROJECT_ZOMBIE_SHOOTER_FB_TO_SFML_CPP_H
