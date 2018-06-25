//
// Created on 01/05/2018.
//

#include "Background.h"
#include <iostream>
#include "map_generated.h"
#include "fb_to_sfml.h"
#include "Collision.h"
#include <math.h>

const char MAP_SAVE_FILE[] = "maps.sav";

Background::Background() {

    // MAP SPECIFICATION
    std::string tileSheetPath;

    // LOAD MAP SPECIFICS
    FILE* file = fopen(MAP_SAVE_FILE, "rb");
    if (file == nullptr){ // no file with saved maps was found
        std::cout << "No file with map saves found. Please go to mapEditor at first, to create a map" << std::endl;
    } else {
        fseek(file, 0L, SEEK_END);
        int length = ftell(file);
        fseek(file, 0L, SEEK_SET);
        std::unique_ptr<char> data(new char[length]);
        fread(data.get(), sizeof(char), length, file);
        fclose(file);

        auto mapList = tileMap::UnPackMapList(data.get());

        auto maps = mapList.get();
        if (maps == nullptr){
            std::cout << "File with map saves found, but without maps. Please go to mapEditor at first, to create a map" << std::endl;
        } else {
            std::cout << "File with map saves found, creating map from save." << std::endl;

            auto map = maps->maps[0].get();

            tileSheetPath = map->tileSheetPath;
            tileDimensions = Vec2iToVector2i(*map->tileDimensions);
            tileSheetDimensions = Vec2iToVector2i(*map->tileSheetDimensions);
            mapSize = Vec2iToVector2i(*map->mapDimensions);
            numberOfLayers = map->numberOfLayers;

            // LOAD TILESHEET TEXTURE
            if (!Collision::CreateTextureAndBitmask(tileSheetTexture, tileSheetPath))
                std::cout << "Texture " << tileSheetPath << " not loaded :( ";
            else {
                auto &layers = map->layers;
                for (int layerIndex = 0; layerIndex < numberOfLayers; layerIndex++){

                    auto &tiles = layers[layerIndex].get()->tiles;
                    // create layer
                    tileLayer layer;

                    // modify layer
                    for (int row = 0; row < mapSize.y; row++){
                        for (int column = 0; column < mapSize.x; column++) {

                            int16_t tileTextureId = tiles[row * mapSize.x + column].get()->textureId;

                            if (tileTextureId >= 0) {
                                sf::Vector2i tileTexturePosition(tileTextureId % tileSheetDimensions.x,
                                                                 tileTextureId / tileSheetDimensions.x);
                                if (tileTexturePosition.y >= tileSheetDimensions.y) {
                                    std::cout << "Tile with ID = " << tileTextureId << " doesn't exist on provided sheet.";
                                    layer.push_back(std::move(Tile()));
                                } else {
                                    Tile tile(
                                            tileSheetTexture,
                                            sf::IntRect(tileTexturePosition.x * tileDimensions.x, tileTexturePosition.y * tileDimensions.y,
                                                        tileDimensions.x, tileDimensions.y),
                                            sf::Vector2f(column * tileDimensions.x, row * tileDimensions.y)
                                    );
                                    if (map->collisionLayer[row * mapSize.x + column].get()->layerId == layerIndex)
                                        tile.SetCollidable();
                                    tile.GetSprite().setRotation(tiles[row * mapSize.x + column].get()->rotation);
                                    layer.push_back(std::move(tile));
                                }
                            } else {
                                layer.push_back(std::move(Tile()));
                            }
                        }
                    }
                // push layer to vector
                tileLayers.push_back(std::move(layer));
                }
            }
        }
    }
}

Background::~Background() {

}

sf::Vector2i Background::GetSize() {
    return sf::Vector2i(mapSize.x * tileDimensions.x, mapSize.y * tileDimensions.y);
}

std::vector<sf::Sprite> Background::GetCollidingTileSprite(sf::FloatRect bounds) const {

    std::vector<sf::Sprite> collisions;

    sf::Vector2i positionRounded((int)floor(bounds.left + 0.5), (int)floor(bounds.top + 0.5)); // round position. This solution is OK here because position will never be negative number

    sf::Vector2i tilePosition((positionRounded.x / tileDimensions.x) , (positionRounded.y / tileDimensions.y));
    if(!(tilePosition.x < 0 || tilePosition.x > mapSize.x || tilePosition.y < 0 || tilePosition.y > mapSize.y))
        for (int layer = 0; layer < numberOfLayers; layer++){
            if(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].IsCollidable())
                collisions.push_back(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].GetSprite());
        }

    positionRounded = sf::Vector2i ((int)floor(bounds.left + bounds.width + 0.5), (int)floor(bounds.top + 0.5));

    tilePosition = sf::Vector2i((positionRounded.x / tileDimensions.x) , (positionRounded.y / tileDimensions.y));
    if(!(tilePosition.x < 0 || tilePosition.x > mapSize.x || tilePosition.y < 0 || tilePosition.y > mapSize.y))
        for (int layer = 0; layer < numberOfLayers; layer++){
            if(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].IsCollidable())
                collisions.push_back(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].GetSprite());
        }

    positionRounded= sf::Vector2i ((int)floor(bounds.left + bounds.width + 0.5), (int)floor(bounds.top + bounds.height + 0.5));

    tilePosition = sf::Vector2i((positionRounded.x / tileDimensions.x) , (positionRounded.y / tileDimensions.y));
    if(!(tilePosition.x < 0 || tilePosition.x > mapSize.x || tilePosition.y < 0 || tilePosition.y > mapSize.y))
        for (int layer = 0; layer < numberOfLayers; layer++){
            if(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].IsCollidable())
                collisions.push_back(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].GetSprite());
        }

    positionRounded= sf::Vector2i ((int)floor(bounds.left + 0.5), (int)floor(bounds.top + bounds.height + 0.5));

    tilePosition = sf::Vector2i((positionRounded.x / tileDimensions.x) , (positionRounded.y / tileDimensions.y));
    if(!(tilePosition.x < 0 || tilePosition.x > mapSize.x || tilePosition.y < 0 || tilePosition.y > mapSize.y))
        for (int layer = 0; layer < numberOfLayers; layer++){
            if(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].IsCollidable())
                collisions.push_back(tileLayers[layer][tilePosition.y * mapSize.x + tilePosition.x].GetSprite());
        }

    return collisions;
}
