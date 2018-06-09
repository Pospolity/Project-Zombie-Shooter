//
// Created on 24/05/2018.
//

#include "MainMenu.h"
#include "MapEditor.h"
#include "Game.h"
#include "colorPalette.h"
#include <iostream>
#include <sstream>


const float BTN_MARGIN_HORIZONTAL= 150.0;
const float BTN_MARGIN_DOWN = 70.0;
const int BTN_FONT_SIZE = 128;
const int LOGO_TEXT_SIZE = 202;

MainMenu::MainMenu(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {}

MainMenu::~MainMenu() {}

void MainMenu::init() {

    const float windowSectionHeight = float(mainResources.window->getSize().y) / (NUMBER_OF_BUTTONS + 1);
    const float windowSectionWidth = float(mainResources.window->getSize().x);

    infoText = sf::Text("Zombie shooter!!!",*mainResources.specialFont, LOGO_TEXT_SIZE);
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(windowSectionWidth / 2.0f, windowSectionHeight / 2.0f);
    infoText.setFillColor(DEFAULT_TEXT_ON_BACKGROUND_COLOR);

    // SET BUTTON'S TEXTS
    std::string buttonTexts[NUMBER_OF_BUTTONS];
    buttonTexts[GAME] = "Play game";
    buttonTexts[MAP_EDITOR] = "Map editor";

    // SET BUTTON'S FUNCTIONS
    buttonTriggerFunction buttonTriggerFunctions[NUMBER_OF_BUTTONS];

    buttonTriggerFunctions[GAME] = [&](){ Game(mainResources).Start(); };
    buttonTriggerFunctions[MAP_EDITOR] = [&](){ MapEditor(mainResources).Start(); };

    // SET BUTTON'S CONFIGURATION
    float btnCenterPosX = windowSectionWidth / 2.0f;
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        float btnCenterPosY = (i + 1) * windowSectionHeight + windowSectionHeight / 2.0f;
        btnCenterPosY -= BTN_MARGIN_DOWN / 2.0f; // make the button align to the top of the window section by moving a center of the button up by half the size of a down margin

        buttons[i].SetSize(sf::Vector2f(windowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, windowSectionHeight - BTN_MARGIN_DOWN));
        buttons[i].SetOrigin(OriginPosition::MIDDLE);
        buttons[i].SetPosition(sf::Vector2f(btnCenterPosX, btnCenterPosY));
        buttons[i].SetText(buttonTexts[i].c_str(), *mainResources.specialFont, BTN_FONT_SIZE);
        buttons[i].OnReleasedTriggerFunction(buttonTriggerFunctions[i]);
    }

    // LOAD AND SET BUTTON'S TEXTURES
    for (int i = 0; i < NUMBER_OF_BUTTON_TEXTURES && i < NUMBER_OF_BUTTONS; i++){ // additional condition "i < NUMBER_OF_BUTTONS" makes sure that no more textures than necessary will be loaded and tried to set on not existing button
        std::ostringstream path;
        path << "assets/graphics/button_bckg_" << i + 1 << ".png";
        if (!mainButtonTextures[i].loadFromFile(path.str()))
            std::cout << "texture " << path.str() << " not loaded :( ";
        else
            buttons[i].SetTexture(&mainButtonTextures[i]);
    }


}

void MainMenu::update() {

    /////////////// DEBUG ONLY TODO: delete after debugging
    Game(mainResources).Start();
    ///////////////

    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mainResources.window));

    if (this->IsFocused()){
        for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
            buttons[i].Update(mousePosition);
        }
    }
}

void MainMenu::draw() {

    mainResources.window->draw(infoText);
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        mainResources.window->draw(buttons[i]);

}
