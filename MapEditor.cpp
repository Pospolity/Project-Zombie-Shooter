//
// Created on 04/05/2018.
//

#include <iostream>
#include "MapEditor.h"


MapEditor::MapEditor(sf::Window &window) : window(window){

}

MapEditor::~MapEditor() {}

void MapEditor::Start() {

    this->isOpen = true;
    std::cout << "Map editor started!" << std::endl;

    /*while(isOpen){

        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){

                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;

            }
        }
    }*/


}


