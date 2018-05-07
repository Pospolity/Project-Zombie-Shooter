//
// Created on 17/04/2018.
//

#include <SFML/Graphics.hpp>
#include "game.h"
#include "mapEditor.h"

enum buttonsOptions {
    GAME, MAP_EDITOR, NUMBER_OF_BUTTONS
};

const int BTN_MARGIN_HORIZONTAL= 150.0;
const int BTN_MARGIN_DOWN = 70.0;
const sf::Color BTN_FILL_COLOR(255, 0, 0);
const int BTN_FONT_SIZE = 64;


int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Hello SFML");

    sf::Font font;
    font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

    sf::RectangleShape windowSections[3];
    const float windowSectionHeight = float(window.getSize().y) / (NUMBER_OF_BUTTONS + 1);
    const float windowSectionWidth = float(window.getSize().x);

    sf::Text infoText("Zombie shooter!!!",font,128);
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(windowSectionWidth / 2.0f, windowSectionHeight / 2.0f);

    struct {
        sf::Text btnText;
        sf::RectangleShape btnField;
        int (*func)(void);
    } buttons[2] = {
            {
                sf::Text("Play game",font,BTN_FONT_SIZE),
                sf::RectangleShape(sf::Vector2f(windowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, windowSectionHeight - BTN_MARGIN_DOWN)),
                &StartGame
            },
            {
                sf::Text("Map editor",font,BTN_FONT_SIZE),
                sf::RectangleShape(sf::Vector2f(windowSectionWidth - BTN_MARGIN_HORIZONTAL* 2, windowSectionHeight - BTN_MARGIN_DOWN)),
                &StartMapEditor
            }
    };

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        auto &btn = buttons[i];
        float btnCenterPosX = windowSectionWidth / 2.0f;
        float btnCenterPosY = (i + 1) * windowSectionHeight + windowSectionHeight / 2.0f;
        btnCenterPosY -= BTN_MARGIN_DOWN / 2.0f; // make the button align to the top of the window section by moving a center of the button up by half the size of a down margin
        sf::FloatRect btnTextRect = btn.btnText.getLocalBounds();
        btn.btnText.setOrigin(btnTextRect.left + btnTextRect.width / 2.0f, btnTextRect.top + btnTextRect.height / 2.0f);
        btn.btnText.setPosition(btnCenterPosX, btnCenterPosY);
        btn.btnField.setPosition(BTN_MARGIN_HORIZONTAL, (i + 1) * windowSectionHeight);
        btn.btnField.setFillColor(BTN_FILL_COLOR);
    }


    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
                        auto &btn = buttons[i];
                        sf::FloatRect btnFieldRect = btn.btnField.getGlobalBounds();
                        if (event.mouseButton.x >= btnFieldRect.left
                            && event.mouseButton.x <= btnFieldRect.left + btnFieldRect.width
                            && event.mouseButton.y >= btnFieldRect.top
                            && event.mouseButton.y <= btnFieldRect.top + btnFieldRect.height)
                            btn.func();
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(infoText);
        for (const auto &btn : buttons){
            window.draw(btn.btnField);
            window.draw(btn.btnText);
        }

        window.display();
    }

    return 0;
}

