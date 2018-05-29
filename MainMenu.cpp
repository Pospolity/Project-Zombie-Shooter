//
// Created on 24/05/2018.
//

#include "MainMenu.h"
#include "MapEditor.h"


const float BTN_MARGIN_HORIZONTAL= 150.0;
const float BTN_MARGIN_DOWN = 70.0;
const sf::Color BTN_FILL_COLOR(255, 0, 0);
const int BTN_FONT_SIZE = 64;

MainMenu::MainMenu(const MainResources & mainResources) : mainResources(mainResources), MainWindow(*(mainResources.window)) {}

MainMenu::~MainMenu() {}

void MainMenu::init() {

    const float windowSectionHeight = float(mainResources.window->getSize().y) / (NUMBER_OF_BUTTONS + 1);
    const float windowSectionWidth = float(mainResources.window->getSize().x);

    infoText = sf::Text("Zombie shooter!!!",*mainResources.defaultFont,128);
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(windowSectionWidth / 2.0f, windowSectionHeight / 2.0f);

    // SET BUTTON'S TEXTS
    std::string buttonTexts[NUMBER_OF_BUTTONS];
    buttonTexts[GAME] = "Play game";
    buttonTexts[MAP_EDITOR] = "Map editor";

    // SET BUTTON'S FUNCTIONS
    buttonTriggerFunction onReleased = [&](){ MapEditor(mainResources).Start(); };
    buttons[MAP_EDITOR].OnReleasedTriggerFunction(onReleased);

    // SET BUTTON'S CONFIGURATION
    float btnCenterPosX = windowSectionWidth / 2.0f;
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        float btnCenterPosY = (i + 1) * windowSectionHeight + windowSectionHeight / 2.0f;
        btnCenterPosY -= BTN_MARGIN_DOWN / 2.0f; // make the button align to the top of the window section by moving a center of the button up by half the size of a down margin

        buttons[i].SetSize(sf::Vector2f(windowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, windowSectionHeight - BTN_MARGIN_DOWN));
        buttons[i].SetOrigin(OriginPosition::MIDDLE);
        buttons[i].SetPosition(sf::Vector2f(btnCenterPosX, btnCenterPosY));
        buttons[i].SetFillColor(BTN_FILL_COLOR);
        buttons[i].SetText(buttonTexts[i].c_str(), *mainResources.defaultFont, BTN_FONT_SIZE);
    }
}

void MainMenu::update() {

    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mainResources.window));
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        buttons[i].Update(mousePosition);
    }
}

void MainMenu::draw() {

    mainResources.window->draw(infoText);
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        mainResources.window->draw(buttons[i]);
}
