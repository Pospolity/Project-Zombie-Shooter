//
// Created on 05/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
#define PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H

#include <SFML/Graphics.hpp>
#include "MainWindow.h"
#include "UI_Button.h"
#include "MainResources.h"

class UI_Button;

const int MAX_NUMBER_OF_LAYERS = 3;
const sf::Vector2i MAX_SIZE_OF_MAP = sf::Vector2i(20, 20);
const sf::Vector2i TILE_DIMENSIONS(128, 128);
const sf::Vector2i TILE_SHEET_DIMENSIONS(27, 20);
const sf::Vector2i TILE_BUTTONS_SHEET_DIMENSIONS(15, 36);
const float TILES_BUTTON_SHEET_ZOOM = 2.0f;
const sf::Vector2f TILES_BUTTON_SHEET_PART_OF_WINDOW(0.5f, 0.80f);
const sf::Vector2f MAP_PART_OF_WINDOW(0.5f, 0.80f);
const float MAP_ZOOM = 1.0f;
const float MAP_SLIDING_STEP = 10.0f; // step in px
const int LAYER_WITH_COLLISIONS = 1; // temporary set to second layer TODO: create possibility to set layer

const char TILE_SHEET_PATH[] = "assets/graphics/tilesheet.png";

struct MapEditorTile {
    UI_Button button;
    int16_t id = -1;
};
typedef std::vector<std::vector<MapEditorTile>> TileMapLayer;

struct TilePicker {
    sf::RectangleShape preview;
    int16_t tileId;
};

struct MapEditorSpec {
    int maxNumberOfLayers = MAX_NUMBER_OF_LAYERS;
    sf::Vector2i mapDimensions = MAX_SIZE_OF_MAP;
    sf::Vector2i tileDimensions = TILE_DIMENSIONS;
    sf::Vector2i tileSheetDimensions = TILE_SHEET_DIMENSIONS;
    sf::Vector2i tileButtonsSheetDimensions = TILE_BUTTONS_SHEET_DIMENSIONS;
    float tilesButtonSheetZoom = TILES_BUTTON_SHEET_ZOOM;
    sf::Vector2f tilesButtonSheetPartOfWindow = TILES_BUTTON_SHEET_PART_OF_WINDOW;
    sf::Vector2f mapPartOfWindow = MAP_PART_OF_WINDOW;
    float mapZoom = MAP_ZOOM;
    std::string tileSheetPath = TILE_SHEET_PATH;
};

class MapEditor : public MainWindow {

public:
    MapEditor(const MainResources & mainResources);
    ~MapEditor();
    bool SaveMap(); // TODO: extract to class mapSaver

private:
    void init() override;
    void update() override;
    void draw() override;

    const MainResources & mainResources;
    UI_Button goBackBtn;
    UI_Button saveBtn;
    sf::View mapView;
    sf::View tilesView;
    sf::View fixedView;
    TilePicker tilePicker;
    int currentLayer = -1; // means that no layer exists
    int numberOfLayers = 0;
    sf::Vector2i tileMapSize;
    std::vector<UI_Button> layerButtons;
    std::vector<TileMapLayer> tileMapLayers;
    std::vector<MapEditorTile> tileButtonsSheet;
    UI_Button tileSheetUpBtn;
    UI_Button tileSheetDownBtn;
    std::vector<UI_Button> layerChooseButtons;
    sf::Texture tileSheetTexture;
    bool isReady = false;
    int loopsToNextRClick = 0; // TODO: replace this solution with timer
    MapEditorSpec spec;

    void setGoBackButton();
    void setSaveButton();
    void setViews();
    void createTilePicker();
    void setButtonsControllingTilesheet();
    // 2 following functions must be called after successfuly setting a tileSheetTexture
    void createTileSheet();
    void createTileMap();
    void createNewLayer();
    void createButtonsToChooseLayer();

    void updateTileSheetButtons(const sf::Vector2i& mousePosition, const sf::Vector2f& onTileSheetMousePosition);
    void updateMapButtons(const sf::Vector2i& mousePosition, const sf::Vector2f& onMapMousePosition);
    void updateFixedButtons(const sf::Vector2i& mousePosition);
    void handleSlidingMap();

};

#endif //PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
