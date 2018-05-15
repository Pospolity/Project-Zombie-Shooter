//
// Created on 17/04/2018.
//

#include <SFML/Graphics.hpp>
#include "game.h"
#include "mapEditor.h"
#include "UI_Button.h"
#include <iostream>
#include <string>

enum buttonsOptions {
    GAME, MAP_EDITOR, NUMBER_OF_BUTTONS
};

const float BTN_MARGIN_HORIZONTAL= 150.0;
const float BTN_MARGIN_DOWN = 70.0;
const sf::Color BTN_FILL_COLOR(255, 0, 0);
const int BTN_FONT_SIZE = 64;


int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Hello SFML");

    sf::Font font;
    font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

    const float windowSectionHeight = float(window.getSize().y) / (NUMBER_OF_BUTTONS + 1);
    const float windowSectionWidth = float(window.getSize().x);

    sf::Text infoText("Zombie shooter!!!",font,128);
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(windowSectionWidth / 2.0f, windowSectionHeight / 2.0f);

    // SET BUTTON'S TEXTS
    UI_Button buttons[NUMBER_OF_BUTTONS];
    std::string buttonTexts[NUMBER_OF_BUTTONS];
    buttonTexts[GAME] = "Play game";
    buttonTexts[MAP_EDITOR] = "Map editor";

    // SET BUTTON'S HANDLER FUNCTIONS
    buttonHandlerFunction buttonFunctions[NUMBER_OF_BUTTONS];
    buttonFunctions[GAME] = StartGame;
    buttonFunctions[MAP_EDITOR] = StartMapEditor;

    // SET BUTTON'S CONFIGURATION
    float btnCenterPosX = windowSectionWidth / 2.0f;
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        float btnCenterPosY = (i + 1) * windowSectionHeight + windowSectionHeight / 2.0f;
        btnCenterPosY -= BTN_MARGIN_DOWN / 2.0f; // make the button align to the top of the window section by moving a center of the button up by half the size of a down margin

        buttons[i].SetSize(sf::Vector2f(windowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, windowSectionHeight - BTN_MARGIN_DOWN));
        sf::FloatRect btnRect = buttons[i].GetLocalBounds();
        buttons[i].SetOrigin(sf::Vector2f(btnRect.left + btnRect.width / 2.0f, btnRect.top + btnRect.height / 2.0f));
        buttons[i].SetPosition(sf::Vector2f(btnCenterPosX, btnCenterPosY));
        buttons[i].SetFillColor(BTN_FILL_COLOR);
        buttons[i].SetText(buttonTexts[i].c_str(), font, BTN_FONT_SIZE);
        buttons[i].SetHandlerFunction(buttonFunctions[i]);
    }


    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved:
                    //handle mouse move event
                    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
                        buttons[i].HandleMouseMoveEvent(event.mouseMove);
                    break;

                case sf::Event::MouseButtonPressed:
                    // handle mouse button pressed event
                    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
                        buttons[i].HandleMouseButtonPressedEvent(event.mouseButton);
                    break;

                case sf::Event::MouseButtonReleased:
                    // handle mouse button released event
                    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
                        buttons[i].HandleMouseButtonReleasedEvent(event.mouseButton);
                    break;

                default:
                    break;

            }
        }

        window.clear(sf::Color::Black);

        window.draw(infoText);
        for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
            window.draw(buttons[i]);

        window.display();
    }

    return 0;
}

