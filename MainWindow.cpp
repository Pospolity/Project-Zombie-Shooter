//
// Created on 22/05/2018.
//

#include "MainWindow.h"
#include "MainResources.h"

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

                default:
                    break;
            }
        }

        update();

        window.clear(sf::Color::Black);

        draw();

        window.display();
    }

}

void MainWindow::ShouldExit() {
    shouldExit = true;
}
