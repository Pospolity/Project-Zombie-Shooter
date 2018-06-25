//
// Created on 01/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H
#define PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H


#include <SFML/Graphics.hpp>
#include "Tile.h"

typedef std::vector<Tile> tileLayer;

class Background : public sf::Drawable {

public:
    Background();
    ~Background();
    sf::Vector2i GetSize();
    std::vector<sf::Sprite>  GetCollidingTileSprite(sf::FloatRect bounds) const;

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (const tileLayer &tileLayer : tileLayers)
            for (const Tile &tile : tileLayer)
                target.draw(tile, states);
    };

    sf::Texture tileSheetTexture;
    std::vector<tileLayer> tileLayers;
    sf::Vector2i mapSize;
    int numberOfLayers;
    sf::Vector2i tileDimensions;
    sf::Vector2i tileSheetDimensions;
};


#endif //PROJECT_ZOMBIE_SHOOTER_BACKGROUND_H
