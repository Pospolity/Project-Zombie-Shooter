//
// Created on 04/05/2018.
//

#include <iostream>
#include "Game.h"
#include <sstream>
#include <math.h>

const float BTN_MARGIN_HORIZONTAL= 300.0;
const float BTN_MARGIN_DOWN = 35.0;
const int BTN_FONT_SIZE = 64;
const int PAUSE_TEXT_FONT_SIZE = 96;
const sf::Vector2f ZOMBIES_IMAGE_SIZE(900, 450);
const float AREA_OF_PROTAGONIST_FOV = 400.0f;


const float PI = 3.14159265f;

Game::Game(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {}

Game::~Game() {}

void Game::init() {

    const float pauseWindowSectionHeight = float(mainResources.window->getSize().y) / (PauseButtonsOptions::NUMBER_OF_BUTTONS + 1);
    const float pauseWindowSectionWidth = float(mainResources.window->getSize().x);

    infoText = sf::Text("GAME PAUSED",*mainResources.specialFont,PAUSE_TEXT_FONT_SIZE);
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(pauseWindowSectionWidth / 2.0f, pauseWindowSectionHeight / 2.0f);

    // SET PAUSE BUTTONS' TEXTS
    std::string buttonTexts[PauseButtonsOptions::NUMBER_OF_BUTTONS];
    buttonTexts[PauseButtonsOptions::CONTINUE] = "Return to game";
    buttonTexts[PauseButtonsOptions::SAVE_GAME] = "Save game";
    buttonTexts[PauseButtonsOptions::LOAD_GAME] = "Load game";
    buttonTexts[PauseButtonsOptions::NEW_GAME] = "New game";
    buttonTexts[PauseButtonsOptions::OPTIONS] = "Options";
    buttonTexts[PauseButtonsOptions::EXIT] = "Exit game";

    // SET PAUSE BUTTON'S FUNCTIONS
    buttonTriggerFunction buttonTriggerFunctions[PauseButtonsOptions::NUMBER_OF_BUTTONS] {};

    buttonTriggerFunctions[PauseButtonsOptions::CONTINUE] = [&](){
        gameState = RUNNING;
        mainResources.window->setMouseCursorVisible(false);
    };
    buttonTriggerFunctions[PauseButtonsOptions::NEW_GAME] = [&](){
        gameState = RUNNING;
        pauseButtons[PauseButtonsOptions::NEW_GAME].Disable();
        pauseButtons[PauseButtonsOptions::CONTINUE].Show();
        pauseButtons[PauseButtonsOptions::SAVE_GAME].Show();
        mainResources.window->setMouseCursorVisible(false);
    };
    buttonTriggerFunctions[PauseButtonsOptions::EXIT] = [&](){ gameState = FINISHED; };

    // SET PAUSE BUTTON'S CONFIGURATION
    float btnCenterPosX = pauseWindowSectionWidth / 2.0f;
    for (int i = 0; i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++) {
        float btnCenterPosY = (i + 1) * pauseWindowSectionHeight + pauseWindowSectionHeight / 2.0f;
        btnCenterPosY -= BTN_MARGIN_DOWN / 2.0f; // make the button align to the top of the window section by moving a center of the button up by half the size of a down margin

        pauseButtons[i].SetSize(sf::Vector2f(pauseWindowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, pauseWindowSectionHeight - BTN_MARGIN_DOWN));
        pauseButtons[i].SetOrigin(OriginPosition::MIDDLE);
        pauseButtons[i].SetPosition(sf::Vector2f(btnCenterPosX, btnCenterPosY));
        pauseButtons[i].SetFillColor(DEFAULT_BTN_FILL_COLOR);
        if (!buttonTexts[i].empty())
            pauseButtons[i].SetText(buttonTexts[i].c_str(), *mainResources.specialFont, BTN_FONT_SIZE);
        if (buttonTriggerFunctions[i] != nullptr)
            pauseButtons[i].OnReleasedTriggerFunction(buttonTriggerFunctions[i]);
    }

    // LOAD AND SET PAUSE BUTTON'S TEXTURES
    for (int i = 0; i < Game::NUMBER_OF_BUTTON_TEXTURES && i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++){ // additional condition "i < NUMBER_OF_BUTTONS" makes sure that no more textures than necessary will be loaded and tried to set on not existing button
        std::ostringstream path;
        path << "assets/graphics/button_bckg_" << i + 1 << ".png";
        if (!pauseButtonTextures[i].loadFromFile(path.str()))
            std::cout << "texture " << path.str() << " not loaded :( ";
        else
            pauseButtons[i].SetTexture(&pauseButtonTextures[i]);
    }

    // DISABLE NOT IMPLEMENTED PAUSE BUTTONS
    pauseButtons[PauseButtonsOptions::SAVE_GAME].Disable();
    pauseButtons[PauseButtonsOptions::LOAD_GAME].Disable();
    pauseButtons[PauseButtonsOptions::OPTIONS].Disable();


    // HIDE BUTTONS NOT AVAILABLE IN INITIAL MENU
    pauseButtons[PauseButtonsOptions::CONTINUE].Hide();
    pauseButtons[PauseButtonsOptions::SAVE_GAME].Hide();


    // LOAD FANCY ZOMBIE IMAGE FOR INITIAL_MENU
    if (!zombiesImageTexture.loadFromFile("assets/graphics/zombies_img.png"))
        std::cout << "texture zombies_img not loaded :( ";
    else {
        zombiesImage.setSize(ZOMBIES_IMAGE_SIZE);
        zombiesImage.setFillColor(DEFAULT_TEXT_ON_BACKGROUND_COLOR);
        zombiesImage.setOrigin(ZOMBIES_IMAGE_SIZE.x / 2.0f, ZOMBIES_IMAGE_SIZE.y / 2.0f);
        zombiesImage.setPosition(pauseWindowSectionWidth / 2.0f, 3.0f * pauseWindowSectionHeight / 2.0f);
        zombiesImage.setTexture(&zombiesImageTexture);
    }

    // SET PROTAGONIST INITIAL POSITION
    gameResources.getProtagonist().SetPosition(mainResources.window->getDefaultView().getCenter() / 2.0f); // TODO: load it from settings in save or in map

    // SET FPS COUNTER
    FPSCounter = sf::Text("", *mainResources.defaultFont, 64);
    FPSCounter.setFillColor(DEFAULT_TEXT_ON_BACKGROUND_COLOR);

    // SET INITIAL GAME STATE
    gameState = INITIAL_MENU;

    // START TIMER
    updateTimer.restart();

    // SET VIEWS
    cameraView = fixedView = mainResources.window->getDefaultView();
    cameraView.zoom(0.90f);

    // SET WINDOW CENTER
    windowCenter = sf::CircleShape(10);

    windowCenter.setOrigin((windowCenter.getLocalBounds().left + windowCenter.getLocalBounds().width) / 2.0f, (windowCenter.getLocalBounds().top + windowCenter.getLocalBounds().height) / 2.0f); // set origin to the middle
    windowCenter.setPosition( mainResources.window->getDefaultView().getCenter() );
    windowCenter.setFillColor(sf::Color::Red);

    // SET AREA OF CAMERA MOVEMENT
    areaOfCameraMovement = sf::CircleShape(AREA_OF_PROTAGONIST_FOV);
    areaOfCameraMovement.setFillColor(sf::Color::Transparent);
    areaOfCameraMovement.setOutlineColor(sf::Color::Blue);
    areaOfCameraMovement.setOutlineThickness(5.0f);
    areaOfCameraMovement.setOrigin(areaOfCameraMovement.getLocalBounds().width / 2.0f, areaOfCameraMovement.getLocalBounds().height / 2.0f); // set origin to the middle
    areaOfCameraMovement.setPosition( cameraView.getCenter().x, cameraView.getCenter().y );

    // LOAD AND SET CROSSHAIR TEXTURE
    if (!crosshairTexture.loadFromFile("assets/graphics/crosshair.png"))
        std::cout << "texture of crosshair not loaded :( ";
    else {
        crosshair.setTexture(crosshairTexture);
        crosshair.setOrigin(crosshair.getLocalBounds().width / 2.0f, crosshair.getLocalBounds().height / 2.0f);
    }

}

void Game::update() {

    sf::Time timeSinceLastUpdate = updateTimer.getElapsedTime();
    updateTimer.restart();

    sf::Vector2i realMousePosition(sf::Mouse::getPosition(*(mainResources.window))); // mouse position relative to game window
    sf::Vector2f mousePositionInFixedView = mainResources.window->mapPixelToCoords(realMousePosition, fixedView);
    sf::Vector2f mousePositionInGameWorld = mainResources.window->mapPixelToCoords(realMousePosition, cameraView); // mouse position translated to position in game coordinates in camera view

    if (this->IsFocused()) {

        if (gameState == PAUSED || gameState == INITIAL_MENU) {
            for (int i = 0; i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++) {
                pauseButtons[i].Update(mousePositionInFixedView);
            }
        }

        if (gameState == RUNNING) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                gameState = PAUSED;
                mainResources.window->setMouseCursorVisible(true);
            }

            gameResources.getProtagonist().Update(mousePositionInGameWorld, timeSinceLastUpdate);
            gameResources.getProtagonist().HandleCollisionWithBackground(gameResources.getBackground());
            areaOfCameraMovement.setPosition(gameResources.getProtagonist().GetPosition().x, gameResources.getProtagonist().GetPosition().y);
            updateCameraPosition(mousePositionInGameWorld);
            crosshair.setPosition(mousePositionInFixedView);

            for (auto &zombie : gameResources.getZombies()){
                zombie.Update(gameResources.getProtagonist(), timeSinceLastUpdate);
                zombie.HandleCollisionWithBackground(gameResources.getBackground());
            }

            gameResources.SpawnZombieIfTimeHasCome(timeSinceLastUpdate, gameResources.getProtagonist().GetPosition(), gameResources.getBackground().GetSize());
            if (gameResources.getProtagonist().IsDead()){
                gameState = DEAD;
            }
        }

        if (gameState == FINISHED)
            ShouldExit();

        if (gameState == DEAD){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                gameState = INITIAL_MENU;
                mainResources.window->setMouseCursorVisible(true);
            }
        }
    }

    calculateFPS(timeSinceLastUpdate);
}

void Game::draw() {

    if (gameState == INITIAL_MENU){
        mainResources.window->draw(zombiesImage);
        for (int i = 0; i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++)
            mainResources.window->draw(pauseButtons[i]);
    }

    if (gameState == PAUSED){
        mainResources.window->draw(infoText);
        for (int i = 0; i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++)
            mainResources.window->draw(pauseButtons[i]);
    }

    if (gameState == RUNNING){

        sf::Vector2i worldSize = gameResources.getBackground().GetSize();
        sf::Vector2u windowSize = mainResources.window->getSize();

        // DRAW ELEMENTS FROM CAMERA VIEW
        mainResources.window->setView(cameraView);

        // DRAW BACKGROUND
        mainResources.window->draw(gameResources.getBackground());

        // DRAW PROTAGONIST
        mainResources.window->draw(gameResources.getProtagonist());

        // DRAW ZOMBIES
        for (auto &zombie : gameResources.getZombies())
            mainResources.window->draw(zombie);

        if (debugging) {

            // DRAW CENTER OF PROTAGONIST SPRITE
            sf::CircleShape protagonistCenter(10);
            protagonistCenter.setOrigin(protagonistCenter.getLocalBounds().width/2.0f, protagonistCenter.getLocalBounds().height/2.0f);
            protagonistCenter.setPosition(gameResources.getProtagonist().GetPosition());
            mainResources.window->draw(protagonistCenter);

            // DRAW AREA OF CAMERA STABILITY
            mainResources.window->draw(areaOfCameraMovement);
        }

        // DRAW FIXED ELEMENTS
        mainResources.window->setView(fixedView);

        if (debugging) {

            // DRAW CIRCLE SIGNING DEFAULT/FIXED VIEW CENTER / CAMERA
            mainResources.window->draw(windowCenter);
        }

        // DRAW FPS COUNTER
        mainResources.window->draw(FPSCounter);

        // DRAW BLOOD
        sf::RectangleShape blood(fixedView.getSize());
        blood.setFillColor(sf::Color(255, 0, 0, ((float)(gameResources.getProtagonist().GetMaxHP() - gameResources.getProtagonist().GetHP()) / (float)(gameResources.getProtagonist().GetMaxHP())) * 255.0f ));
        mainResources.window->draw(blood);

        // DRAW CROSSHAIR
        mainResources.window->draw(crosshair);
    }

    if (gameState == DEAD){
        sf::Text lastMessage("YOU ARE DEAD!", *mainResources.specialFont, 200);
        lastMessage.setOrigin((lastMessage.getLocalBounds().left + lastMessage.getLocalBounds().width)/ 2.0f, (lastMessage.getLocalBounds().top + lastMessage.getLocalBounds().height)/ 2.0f);
        lastMessage.setPosition(fixedView.getCenter());
        lastMessage.setFillColor(sf::Color::Red);
        lastMessage.setOutlineColor(sf::Color::Black);
        lastMessage.setOutlineThickness(20);
        mainResources.window->draw(lastMessage);
    }
}

void Game::calculateFPS(const sf::Time &timeSinceLastUpdate) {
    float FPS = 1.0f / timeSinceLastUpdate.asSeconds();
    std::ostringstream FPSCounterText;
    FPSCounterText << floor(FPS + 0.5); // round FPS. This solution is OK here because FPS will never be negative number
    FPSCounter.setString(FPSCounterText.str());
}

void Game::updateCameraPosition(const sf::Vector2f &mousePosition) {

        sf::Vector2f mouseFromProtagonistDistance;

        mouseFromProtagonistDistance.x = gameResources.getProtagonist().GetPosition().x - mousePosition.x;
        mouseFromProtagonistDistance.y = gameResources.getProtagonist().GetPosition().y - mousePosition.y;

        sf::Vector2f newCameraPosition;

        newCameraPosition.x = gameResources.getProtagonist().GetPosition().x - mouseFromProtagonistDistance.x * 0.5f;
        newCameraPosition.y = gameResources.getProtagonist().GetPosition().y - mouseFromProtagonistDistance.y * 0.5f;

        if (!intersects(areaOfCameraMovement, newCameraPosition)) {

            float angle = getAngleInRadians(gameResources.getProtagonist().GetPosition(), mousePosition);

            newCameraPosition.x = gameResources.getProtagonist().GetPosition().x - areaOfCameraMovement.getRadius() * cos(angle);
            newCameraPosition.y = gameResources.getProtagonist().GetPosition().y - areaOfCameraMovement.getRadius() * sin(angle);
        }

    cameraView.setCenter(newCameraPosition.x, newCameraPosition.y);
}

bool Game::intersects(const sf::CircleShape &circle, const sf::Vector2f &point)
{
    sf::Vector2f circleDistance;
    circleDistance.x = abs(circle.getPosition().x - point.x);
    circleDistance.y = abs(circle.getPosition().y - point.y);

    if (circleDistance.x >  circle.getRadius()) { return false; }
    if (circleDistance.y >  circle.getRadius()) { return false; }

    if (circleDistance.x <= 1) { return true; }
    if (circleDistance.y <= 1) { return true; }

    float cornerDistance_sq = pow(circleDistance.x, 2) + pow(circleDistance.y, 2);

    return (cornerDistance_sq <= pow(circle.getRadius(), 2));
}

float Game::getAngleInRadians(const sf::Vector2f &center, const sf::Vector2f &point){

    sf::Vector2f diff = center - point;
    return atan2f(diff.y, diff.x);
}