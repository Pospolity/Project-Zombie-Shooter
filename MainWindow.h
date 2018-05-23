//
// Created on 22/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_MAINWINDOW_H
#define PROJECT_ZOMBIE_SHOOTER_MAINWINDOW_H


#include <SFML/Graphics.hpp>
#include "MainResources.h"

class MainWindow {
public:
    MainWindow(sf::RenderWindow & window);
    virtual ~MainWindow();
    void Start();
    void ShouldExit();

private:
    bool shouldExit;
    sf::RenderWindow & window;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};


#endif //PROJECT_ZOMBIE_SHOOTER_MAINWINDOW_H
