//
// Created on 05/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
#define PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H

#include <SFML/Graphics.hpp>
#include "MainWindow.h"
#include "UI_Button.h"
#include "MainResources.h"

class MapEditor : public MainWindow {

public:
    MapEditor(const MainResources & mainResources);
    ~MapEditor();

private:
    void init() override;
    void update() override;
    void draw() override;

    const MainResources & mainResources;
    UI_Button goBackBtn;
};

#endif //PROJECT_ZOMBIE_SHOOTER_MAPEDITOR_H
