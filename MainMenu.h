//
// Created on 24/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAINMENU_H
#define PROJECT_ZOMBIE_SHOOTER_MAINMENU_H

#include "MainWindow.h"
#include "GameResources.h"
#include "UI_Button.h"

const int NUMBER_OF_BUTTON_TEXTURES = 2;

enum buttonsOptions {
    GAME, MAP_EDITOR, NUMBER_OF_BUTTONS
};

class MainMenu : public MainWindow {
public:
    MainMenu(const MainResources & MainResources);
    ~MainMenu();

private:
    void init() override ;
    void update() override ;
    void draw() override ;

    const MainResources & mainResources;
    UI_Button buttons[NUMBER_OF_BUTTONS];
    sf::Text infoText;

    sf::Texture mainButtonTextures[NUMBER_OF_BUTTON_TEXTURES];

    void setInfoText(float windowSectionHeight, float windowSectionWidth);
    void setButtons(float windowSectionHeight, float windowSectionWidth);

};





#endif //PROJECT_ZOMBIE_SHOOTER_MAINMENU_H
