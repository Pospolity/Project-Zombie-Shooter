//
// Created on 22/05/2018.
//

#include "MainWindow.h"
#include "MainResources.h"
#include "colorPalette.h"

MainWindow::MainWindow(sf::RenderWindow & window) : window(window) {}

MainWindow::~MainWindow() {}

void MainWindow::Start() {

    shouldExit = false;
    init();

    while(window.isOpen() && !shouldExit) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::LostFocus:
                    isFocused = false;
                    break;

                case sf::Event::GainedFocus:
                    isFocused = true;
                    break;

                default:
                    break;
            }
        }

        update();

        window.clear(DEFAULT_BACKGROUND_COLOR);

        draw();

        window.display();
    }

}

void MainWindow::ShouldExit() {
    shouldExit = true;
}
