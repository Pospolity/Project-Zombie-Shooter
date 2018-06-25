//
// Created on 11/06/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_TILE_H
#define PROJECT_ZOMBIE_SHOOTER_TILE_H


#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable{
public:
    Tile() = default;
    Tile(Tile&& tile) : tileSprite(std::move(tile.tileSprite)), collidable(tile.collidable) {};
    Tile(const sf::Texture &tileMapTexture, const sf::IntRect &tilePositionOnTexture, const sf::Vector2f tilePosition);
    ~Tile() = default;

    bool IsCollidable() const { return collidable; };
    void SetCollidable() { collidable = true; };
    sf::Sprite& GetSprite() const { return *tileSprite; };

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if(tileSprite != nullptr)
            target.draw(*tileSprite, states);
    };

    std::unique_ptr<sf::Sprite> tileSprite = nullptr;
    bool collidable = false;
};


#endif //PROJECT_ZOMBIE_SHOOTER_TILE_H
