//
// Created on 11/06/2018.
//

#include "Tile.h"

Tile::Tile(const sf::Texture &tileMapTexture, const sf::IntRect &tilePositionOnTexture, const sf::Vector2f tilePosition)
    : tileSprite(std::unique_ptr<sf::Sprite>(new sf::Sprite(tileMapTexture, tilePositionOnTexture))) {

    sf::FloatRect bounds = tileSprite->getLocalBounds();
    tileSprite->setOrigin((bounds.left + bounds.width) / 2.0f, (bounds.top + bounds.height) / 2.0f );
    tileSprite->setPosition(tilePosition);
}
