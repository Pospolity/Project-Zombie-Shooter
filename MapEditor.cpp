//
// Created on 04/05/2018.
//

#include <iostream>
#include <sstream>
#include "MapEditor.h"
#include "UI_Button.h"
#include "MainWindow.h"
#include "map_generated.h"
#include <cstdio>
#include "fb_to_sfml.h"

const char MAP_SAVE_FILE[] = "maps.sav";
const int NO_LAYER_SPECIFIED = (-1);

MapEditor::MapEditor(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {}

MapEditor::~MapEditor() {}

void MapEditor::init() {

    setGoBackButton();

    setSaveButton();

    setViews();

    createTilePicker();

    // LOAD MAP SPECIFICS
    FILE* file = fopen(MAP_SAVE_FILE, "rb");
    if (file == nullptr){ // if no file with saved maps was found
        std::cout << "No file with map saves found. Creating new map" << std::endl;

        // LOAD TILESHEET TEXTURE
        if (!tileSheetTexture.loadFromFile(spec.tileSheetPath))
            std::cout << "Texture " << spec.tileSheetPath << " not loaded :( ";
        else {

            // CREATE TILE SHEET
            createTileSheet();

            // CREATE GRID OF MAP TILES
            createTileMap();
        }
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
            std::cout << "File with map saves found, but without maps. Creating new map" << std::endl;

            // LOAD TILESHEET TEXTURE
            if (!tileSheetTexture.loadFromFile(spec.tileSheetPath))
                std::cout << "Texture " << spec.tileSheetPath << " not loaded :( ";
            else {

                // CREATE TILE SHEET
                createTileSheet();

                // CREATE GRID OF MAP TILES
                createTileMap();
            }
        } else {
            std::cout << "File with map saves found, creating map from save." << std::endl;

            auto map = maps->maps[0].get();

            spec.tileSheetPath = map->tileSheetPath;
            spec.tileDimensions = Vec2iToVector2i(*map->tileDimensions);
            spec.tileSheetDimensions = Vec2iToVector2i(*map->tileSheetDimensions);
            spec.mapDimensions = Vec2iToVector2i(*map->mapDimensions);

            // LOAD TILESHEET TEXTURE
            if (!tileSheetTexture.loadFromFile(spec.tileSheetPath))
                std::cout << "Texture " << spec.tileSheetPath << " not loaded :( ";
            else {

                // CREATE TILE SHEET
                createTileSheet();

                // CREATE GRID OF MAP TILES
                for (auto &layer : map->layers){
                    createNewLayer();
                    auto &tiles = layer.get()->tiles;
                    for (int row = 0; row < spec.mapDimensions.y; row++){
                        for (int column = 0; column < spec.mapDimensions.x; column++){
                            int16_t tileTextureId = tiles[row * spec.mapDimensions.y + column].get()->textureId;
                            sf::Vector2i tileTexturePosition(tileTextureId % spec.tileSheetDimensions.x,
                                                             tileTextureId / spec.tileSheetDimensions.x);
                            tileMapLayers[currentLayer][row][column].id = tileTextureId;
                            if (tileMapLayers[currentLayer][row][column].id != (-1)){
                                tileMapLayers[currentLayer][row][column].button.SetTexture(&tileSheetTexture);
                                tileMapLayers[currentLayer][row][column].button.SetTextureRect(sf::IntRect(tileTexturePosition.x * spec.tileDimensions.x, tileTexturePosition.y * spec.tileDimensions.y,
                                                                                               spec.tileDimensions.x, spec.tileDimensions.y));
                                tileMapLayers[currentLayer][row][column].button.SetRotation(tiles[row * spec.mapDimensions.y + column].get()->rotation);
                                tileMapLayers[currentLayer][row][column].button.SetFillColor(sf::Color::White);

                            }
                        }
                    }
                }
            }
        }
    }


    setButtonsControllingTilesheet();

    createButtonsToChooseLayer();

    // SET READINESS OF MAP EDITOR
    isReady = true;
}

void MapEditor::update() {

    sf::Vector2i mousePosition(sf::Mouse::getPosition(*(mainResources.window)));
    sf::Vector2f onTileSheetMousePosition = mainResources.window->mapPixelToCoords(mousePosition, tilesView);
    sf::Vector2f onMapMousePosition = mainResources.window->mapPixelToCoords(mousePosition, mapView);

    if (this->IsFocused()){

        updateTileSheetButtons(mousePosition, onTileSheetMousePosition);

        updateMapButtons(mousePosition, onMapMousePosition);

        updateFixedButtons(mousePosition);

        handleSlidingMap();

        // UPDATE TILE PICKER
        tilePicker.preview.setPosition(sf::Vector2f(mousePosition));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && loopsToNextRClick == 0){
            tilePicker.preview.rotate(90);
            loopsToNextRClick = 20;
        }
        if (loopsToNextRClick != 0)
            loopsToNextRClick--;
    }

}

void MapEditor::draw() {

    // DRAW POSSIBLE TILES
    mainResources.window->setView(tilesView);
    for (int row = 0; row < spec.tileButtonsSheetDimensions.y; row++){
        for (int column = 0; column < spec.tileButtonsSheetDimensions.x; column++) {
            mainResources.window->draw(tileButtonsSheet[(row * spec.tileButtonsSheetDimensions.x) + column].button);
        }
    }

    // DRAW MAP
    mainResources.window->setView(mapView);
    for (int layer = 0; layer < numberOfLayers; layer++){
        for (std::vector<MapEditorTile> &tilesRow : tileMapLayers[layer]){
            for (MapEditorTile &tile : tilesRow){
                if (layer > currentLayer) {
                    sf::Color tileColor = tile.button.GetFillColor();
                    tile.button.SetFillColor(tileColor - sf::Color(0, 0, 0, 150));
                    mainResources.window->draw(tile.button);
                    tile.button.SetFillColor(tileColor);
                } else {
                    mainResources.window->draw(tile.button);
                }
            }
        }
    }

    // DRAW FIXED ELEMENTS
    mainResources.window->setView(fixedView);

    mainResources.window->draw(tilePicker.preview);
    mainResources.window->draw(goBackBtn);
    mainResources.window->draw(saveBtn);
    mainResources.window->draw(tileSheetUpBtn);
    mainResources.window->draw(tileSheetDownBtn);

    for (auto &button : layerChooseButtons)
        mainResources.window->draw(button);

}

bool MapEditor::SaveMap() {
    if (!this->isReady)
        return false;

    flatbuffers::FlatBufferBuilder builder(1028);

    // hardcoded
        // id
    int8_t mapId = 0;
        // name
    auto mapName = "map";
        // tileSheetPath
    auto tileSheetPath = spec.tileSheetPath;
        // tileSheetDimensions
    auto tileSheetDimensions = tileMap::Vec2i(spec.tileSheetDimensions.x, spec.tileSheetDimensions.y);
        // tileDimensions
    auto tileDimensions = tileMap::Vec2i(spec.tileDimensions.x, spec.tileDimensions.y);
        // mapDimensions
    auto mapDimensions = tileMap::Vec2i(spec.mapDimensions.x, spec.mapDimensions.y);
        // numberOfLayers
    int numberOfLayers = this->numberOfLayers; // just for transparency of fields saved, may be deleted
        // layers
    std::vector<flatbuffers::Offset<tileMap::Layer>> layersOffset;
    for (int layer = 0; layer < numberOfLayers; layer++){
        std::vector<flatbuffers::Offset<tileMap::Tile>> tileOffsetsVector;
        for (std::vector<MapEditorTile> &tilesRow : tileMapLayers[layer]){
            for (MapEditorTile &tile : tilesRow){
                auto tileOffset = tileMap::CreateTile(builder, tile.id, tile.button.GetRotation());
                tileOffsetsVector.push_back(std::move(tileOffset));
            }
        }
        auto layerOffset = tileMap::CreateLayerDirect(builder, &tileOffsetsVector);
        layersOffset.push_back(std::move(layerOffset));
    }
        // collisionLayer
    // temporary set to second layer if something exists on it TODO: create possibility to set layer
    std::vector<flatbuffers::Offset<tileMap::CollidingTile>> collidingTilesLayersOffset;
    if (numberOfLayers >= LAYER_WITH_COLLISIONS){
        for (std::vector<MapEditorTile> &tilesRow : tileMapLayers[LAYER_WITH_COLLISIONS]){
            for (MapEditorTile &tile : tilesRow){
                flatbuffers::Offset<tileMap::CollidingTile> collidingTileOffset;
                if (tile.id != (-1))
                    collidingTileOffset = tileMap::CreateCollidingTile(builder, LAYER_WITH_COLLISIONS);
                else
                    collidingTileOffset = tileMap::CreateCollidingTile(builder, NO_LAYER_SPECIFIED);

                collidingTilesLayersOffset.push_back(std::move(collidingTileOffset));
            }
        }
    }

    auto map = tileMap::CreateMapDirect(builder, mapId, mapName, tileSheetPath.c_str(), &tileSheetDimensions, &tileDimensions, &mapDimensions, numberOfLayers, &layersOffset, &collidingTilesLayersOffset);

    std::vector<flatbuffers::Offset<tileMap::Map>> maps;
    maps.push_back(map);

    auto mapList = tileMap::CreateMapListDirect(builder, &maps);

    builder.Finish(mapList);

    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    FILE* file = fopen(MAP_SAVE_FILE, "wb");

    fwrite(buf, size, 1, file);
    fclose(file);

    return true;
}

void MapEditor::setGoBackButton() {
    goBackBtn.SetText("Go back", *(mainResources.defaultFont), 40);
    goBackBtn.SetSize(sf::Vector2f(200, 75));
    goBackBtn.SetFillColor(sf::Color::Red);
    goBackBtn.SetPosition(sf::Vector2f(25, 25));

    buttonTriggerFunction onReleased = std::bind(&MapEditor::ShouldExit, this);
    goBackBtn.OnReleasedTriggerFunction(onReleased);
}

void MapEditor::setSaveButton() {
    saveBtn.SetText("Save", *(mainResources.defaultFont), 40);
    saveBtn.SetSize(sf::Vector2f(200, 75));
    saveBtn.SetFillColor(sf::Color::Red);
    saveBtn.SetPosition(sf::Vector2f(250, 25));

    buttonTriggerFunction onReleased = [&]{
        if (SaveMap())
            std::cout << "map successfully saved";
    };
    saveBtn.OnReleasedTriggerFunction(onReleased);
}

void MapEditor::setViews() {
    mapView = tilesView = fixedView = mainResources.window->getDefaultView();

    float zoom = spec.mapZoom;
    sf::Vector2f partOfWindowOccupied = MAP_PART_OF_WINDOW;
    mapView.setCenter(sf::Vector2f(fixedView.getCenter().x * partOfWindowOccupied.x * zoom, fixedView.getCenter().y * partOfWindowOccupied.y * zoom));
    mapView.setSize(sf::Vector2f(fixedView.getSize().x * partOfWindowOccupied.x, fixedView.getSize().y * partOfWindowOccupied.y));
    mapView.setViewport(sf::FloatRect(0.0f, (1.0f - partOfWindowOccupied.y) / 2.0f, partOfWindowOccupied.x, partOfWindowOccupied.y));

    zoom = spec.tilesButtonSheetZoom;
    partOfWindowOccupied = TILES_BUTTON_SHEET_PART_OF_WINDOW;
    tilesView.setCenter(sf::Vector2f(fixedView.getCenter().x * partOfWindowOccupied.x * zoom, fixedView.getCenter().y * partOfWindowOccupied.y * zoom));
    tilesView.setSize(sf::Vector2f(fixedView.getSize().x * partOfWindowOccupied.x, fixedView.getSize().y * partOfWindowOccupied.y));
    tilesView.setViewport(sf::FloatRect(0.5f, (1.0f - partOfWindowOccupied.y) / 2.0f, partOfWindowOccupied.x, partOfWindowOccupied.y));
    tilesView.zoom(zoom);
}

void MapEditor::createTilePicker() {
    tilePicker.preview.setSize(sf::Vector2f(spec.tileDimensions));
    tilePicker.preview.setOrigin(sf::Vector2f((tilePicker.preview.getLocalBounds().left + tilePicker.preview.getLocalBounds().width) / 2.0f, (tilePicker.preview.getLocalBounds().top + tilePicker.preview.getLocalBounds().height) / 2.0f));
    tilePicker.preview.setTexture(&tileSheetTexture);
    tilePicker.preview.setOutlineThickness(2);
    tilePicker.preview.setOutlineColor(sf::Color::White);
    tilePicker.preview.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void MapEditor::setButtonsControllingTilesheet() {
    buttonTriggerFunction onClicked;
    sf::Vector2f tilesViewRealSize = tilesView.getSize() / spec.tilesButtonSheetZoom;

    tileSheetUpBtn.SetSize(sf::Vector2f(tilesViewRealSize.x, (fixedView.getSize().y - tilesViewRealSize.y) / 2.0f ));
    tileSheetUpBtn.SetFillColor(sf::Color::Black);
    tileSheetUpBtn.SetText("Scroll up", *mainResources.defaultFont);
    tileSheetUpBtn.SetPosition(sf::Vector2f(fixedView.getCenter().x, 0));
    onClicked = [=, &view = tilesView, minimalYPosition = tilesView.getCenter().y]{ // tilesView.getCenter().y return value of tilesView when this lambda was created
        float yPlusOffset = view.getCenter().y + (3 * (-1) * spec.tileDimensions.y); // view.getCenter().y has value of tilesView when this lambda was called
        if (yPlusOffset >= minimalYPosition)
            view.setCenter(view.getCenter().x, yPlusOffset);
    };
    tileSheetUpBtn.OnReleasedTriggerFunction(onClicked);

    tileSheetDownBtn.SetSize(sf::Vector2f(tilesViewRealSize.x, (fixedView.getSize().y - tilesViewRealSize.y) / 2.0f ));
    tileSheetDownBtn.SetFillColor(sf::Color::Black);
    tileSheetDownBtn.SetText("Scroll down", *mainResources.defaultFont);
    tileSheetDownBtn.SetPosition(sf::Vector2f(fixedView.getCenter().x, fixedView.getSize().y - ((fixedView.getSize().y - tilesViewRealSize.y) / 2.0f)));
    onClicked = [=, &view = tilesView]{view.move(0, 3 * spec.tileDimensions.y);};
    tileSheetDownBtn.OnReleasedTriggerFunction(onClicked);
}

void MapEditor::updateTileSheetButtons(const sf::Vector2i &mousePosition, const sf::Vector2f &onTileSheetMousePosition) {
    sf::Vector2f tilesViewRealSize = tilesView.getSize() / spec.tilesButtonSheetZoom;
    if(mousePosition.x > fixedView.getSize().x * TILES_BUTTON_SHEET_PART_OF_WINDOW.x
       && mousePosition.x < fixedView.getSize().x
       && mousePosition.y > (fixedView.getSize().y - tilesViewRealSize.y) / 2.0f
       && mousePosition.y < fixedView.getSize().y - ((fixedView.getSize().y - tilesViewRealSize.y) / 2.0f))
    {
        for (int row = 0; row < spec.tileButtonsSheetDimensions.y; row++){
            for (int column = 0; column < spec.tileButtonsSheetDimensions.x; column++) {
                tileButtonsSheet[(row * spec.tileButtonsSheetDimensions.x) + column].button.Update(onTileSheetMousePosition);
            }
        }
    }
}

void MapEditor::updateFixedButtons(const sf::Vector2i &mousePosition) {
    goBackBtn.Update(sf::Vector2f(mousePosition));
    saveBtn.Update(sf::Vector2f(mousePosition));
    tileSheetUpBtn.Update(sf::Vector2f(mousePosition));
    tileSheetDownBtn.Update(sf::Vector2f(mousePosition));

    for (auto &button : layerChooseButtons)
        button.Update(sf::Vector2f(mousePosition));
}

void MapEditor::updateMapButtons(const sf::Vector2i &mousePosition, const sf::Vector2f &onMapMousePosition) {
    sf::Vector2f mapViewRealSize = mapView.getSize() / spec.mapZoom;
    if(mousePosition.x > 0
       && mousePosition.x < mapViewRealSize.x
       && mousePosition.y > (fixedView.getSize().y - mapViewRealSize.y) / 2.0f
       && mousePosition.y < fixedView.getSize().y - ((fixedView.getSize().y - mapViewRealSize.y) / 2.0f))
    {
        int layer = currentLayer;
        for (std::vector<MapEditorTile> &tilesRow : tileMapLayers[layer]){
            for (MapEditorTile &tile : tilesRow){
                tile.button.Update(onMapMousePosition);
            }
        }
    }
}

void MapEditor::handleSlidingMap() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) mapView.move(0, (-1) * MAP_SLIDING_STEP);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) mapView.move(0, MAP_SLIDING_STEP);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) mapView.move((-1) * MAP_SLIDING_STEP, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) mapView.move(MAP_SLIDING_STEP, 0);
}

void MapEditor::createTileSheet() {
    for (int row = 0; row < spec.tileSheetDimensions.y; row++){
        for (int column = 0; column < spec.tileSheetDimensions.x; column++) {

            MapEditorTile tileButton;

            tileButton.id = row * spec.tileSheetDimensions.x + column;

            tileButton.button.SetSize(sf::Vector2f(spec.tileDimensions));
            tileButton.button.SetTexture(&tileSheetTexture);
            tileButton.button.SetFillColor(sf::Color::White);
            tileButton.button.SetOutlineThickness(-2);
            tileButton.button.SetOutlineColor(sf::Color::White);
            tileButton.button.SetTextureRect(sf::IntRect(column * spec.tileDimensions.x, row * spec.tileDimensions.y, spec.tileDimensions.x, spec.tileDimensions.y));

            buttonTriggerFunction onClicked = [=, &tilePicker = tilePicker]{
                tilePicker.preview.setTextureRect(sf::IntRect(column * spec.tileDimensions.x, row * spec.tileDimensions.y, spec.tileDimensions.x, spec.tileDimensions.y));
                tilePicker.tileId = tileButton.id;
            };
            tileButton.button.OnReleasedTriggerFunction(onClicked);

            tileButtonsSheet.push_back(std::move(tileButton));
        }
    }
    int maxNumberOfTile = (spec.tileSheetDimensions.x * spec.tileSheetDimensions.y) - 1;
    for (int row = 0; row < spec.tileButtonsSheetDimensions.y; row++){
        for (int column = 0; column < spec.tileButtonsSheetDimensions.x; column++) {
            int tileNumber = (row * spec.tileButtonsSheetDimensions.x) + column;
            if (tileNumber > maxNumberOfTile)
                break;
            tileButtonsSheet[tileNumber].button.SetPosition(sf::Vector2f(column * spec.tileDimensions.x, row * spec.tileDimensions.y));
        }
    }
}

void MapEditor::createTileMap() {
    createNewLayer();
}

void MapEditor::createNewLayer() {

    int newLayerNumber = numberOfLayers;
    TileMapLayer tileMapLayer;
    tileMapSize = sf::Vector2i(spec.mapDimensions);
    for (int row = 0; row < tileMapSize.y; row++) {

        std::vector<MapEditorTile> tilesRow;

        for (int column = 0; column < tileMapSize.x; column++) {
            MapEditorTile tile;

            sf::Vector2f TLCPosition = sf::Vector2f(column * spec.tileDimensions.x, row * spec.tileDimensions.y);
            tile.button.SetSize(sf::Vector2f(spec.tileDimensions));
            tile.button.SetPosition(sf::Vector2f(TLCPosition.x + (tile.button.GetSize().x / 2.0f), TLCPosition.y + (tile.button.GetSize().y / 2.0f)));
            tile.button.SetOrigin(OriginPosition::MIDDLE);
            tile.button.SetFillColor(sf::Color::Transparent);
            tile.button.SetOutlineColor(sf::Color::White);
            tile.button.SetOutlineThickness(-2);

            buttonTriggerFunction onClicked = [=, &tilePicker = tilePicker]{
                tileMapLayers[newLayerNumber][row][column].button.SetTexture(tilePicker.preview.getTexture());
                tileMapLayers[newLayerNumber][row][column].button.SetTextureRect(tilePicker.preview.getTextureRect());
                tileMapLayers[newLayerNumber][row][column].button.SetFillColor(sf::Color::White);
                tileMapLayers[newLayerNumber][row][column].button.SetRotation(tilePicker.preview.getRotation());
                tileMapLayers[newLayerNumber][row][column].id = tilePicker.tileId;
            };

            tile.button.OnPressedTriggerFunction(onClicked);
            tilesRow.push_back(std::move(tile));
        }

        tileMapLayer.push_back(std::move(tilesRow));
    }
    tileMapLayers.push_back(std::move(tileMapLayer));

    numberOfLayers++;
    currentLayer = newLayerNumber;
}

void MapEditor::createButtonsToChooseLayer() {
    for (int layerNumber = 0; layerNumber < spec.maxNumberOfLayers; layerNumber++){
        UI_Button button;

        if (layerNumber > numberOfLayers)
            button.Disable();
        button.SetSize(sf::Vector2f(80, 80));
        button.SetOrigin(OriginPosition::MIDDLE);
        button.SetPosition(sf::Vector2f(80 + layerNumber * 90, fixedView.getSize().y - 50));

        std::ostringstream layerNumberAsText("+");
        if (layerNumber < numberOfLayers){
            layerNumberAsText.clear();
            layerNumberAsText << layerNumber;
        }

        button.SetText(layerNumberAsText.str().c_str(), *mainResources.defaultFont);

        layerChooseButtons.push_back(std::move(button));

        buttonTriggerFunction onClick = [&, layerNumber = layerNumber]{
            if (layerNumber >= numberOfLayers) {

                createNewLayer();
                std::ostringstream layerNumberAsText("");
                layerNumberAsText << layerNumber;
                layerChooseButtons[layerNumber].SetText(layerNumberAsText.str().c_str(), *mainResources.defaultFont);
                if (layerNumber < spec.maxNumberOfLayers)
                    layerChooseButtons[layerNumber + 1].Enable();
            }
            currentLayer = layerNumber;
        };
        layerChooseButtons[layerNumber].OnReleasedTriggerFunction(onClick);
    }

}