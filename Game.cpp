//
// Created on 04/05/2018.
//

#include <iostream>
#include "Game.h"
#include <sstream>

const float BTN_MARGIN_HORIZONTAL= 300.0;
const float BTN_MARGIN_DOWN = 35.0;
const int BTN_FONT_SIZE = 64;
const int PAUSE_TEXT_FONT_SIZE = 96;
const sf::Vector2f ZOMBIES_IMAGE_SIZE(900, 450);

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

    buttonTriggerFunctions[PauseButtonsOptions::CONTINUE] = [&](){ gameState = RUNNING; };
    buttonTriggerFunctions[PauseButtonsOptions::NEW_GAME] = [&](){
        gameState = RUNNING;
        pauseButtons[PauseButtonsOptions::NEW_GAME].Disable();
        pauseButtons[PauseButtonsOptions::CONTINUE].Show();
        pauseButtons[PauseButtonsOptions::SAVE_GAME].Show();
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
    gameState = INITIAL_MENU;
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

}

void Game::update() {

    sf::Vector2f mousePosition(sf::Mouse::getPosition(*(mainResources.window)));

    if (this->IsFocused()) {

        if (gameState == PAUSED || gameState == INITIAL_MENU) {
            for (int i = 0; i < PauseButtonsOptions::NUMBER_OF_BUTTONS; i++) {
                pauseButtons[i].Update(mousePosition);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            if (gameState == RUNNING)
                gameState = PAUSED;
        }

        if (gameState == FINISHED)
            ShouldExit();
    }
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
}