//
// Created on 05/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_GAME_H
#define PROJECT_ZOMBIE_SHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include "MainWindow.h"
#include "UI_Button.h"
#include "MainResources.h"
#include "Background.h"
#include "Protagonist.h"



class Game : public MainWindow {
public:
    Game(const MainResources & mainResources);
    ~Game();

private:
    static const int NUMBER_OF_BUTTON_TEXTURES = 6;

    enum GameStates {
        INITIAL_MENU, RUNNING, PAUSED, FINISHED
    };

    struct PauseButtonsOptions { // way to have enumerators which don't need to be unique in whole class, but still implicitly convertible to int
        enum : int {
            CONTINUE, SAVE_GAME, LOAD_GAME, NEW_GAME, OPTIONS, EXIT, NUMBER_OF_BUTTONS
        };
    };

    void init() override;
    void update() override;
    void draw() override;

    void calculateFPS(const sf::Time &timeSinceLastUpdate);
    void updateCameraPosition(const sf::Vector2f &mousePosition);
    bool intersects(const sf::CircleShape &circle, const sf::Vector2f &point);
    float getAngleInRadians(const sf::Vector2f &center, const sf::Vector2f &point);

    const MainResources & mainResources;
    UI_Button pauseButtons[PauseButtonsOptions::NUMBER_OF_BUTTONS];
    sf::Texture pauseButtonTextures[Game::NUMBER_OF_BUTTON_TEXTURES];
    sf::RectangleShape zombiesImage;
    sf::Texture zombiesImageTexture;
    sf::Text infoText;
    GameStates gameState;
    Background background;
    Protagonist protagonist;
    sf::Clock updateTimer;
    sf::Text FPSCounter;
    sf::View cameraView;
    sf::View fixedView;
    sf::CircleShape windowCenter;
    sf::CircleShape areaOfCameraMovement;
    sf::Sprite crosshair; // TODO: create a separate class for crosshair
    sf::Texture crosshairTexture;

    bool debugging = false;
};

#endif //PROJECT_ZOMBIE_SHOOTER_GAME_H
