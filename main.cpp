//
// Created on 17/04/2018.
//

#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Hello SFML");

    sf::Font font;
    font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

    sf::Text text("Hello SFML",font,11);
    text.setCharacterSize(64);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();
        }
    }

    return 0;

}