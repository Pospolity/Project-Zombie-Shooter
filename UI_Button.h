//
// Created on 07/05/2018.
//

#ifndef PROJECT_ZOMBIE_SHOOTER_BUTTON_H
#define PROJECT_ZOMBIE_SHOOTER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

typedef void (*buttonHandlerFunction)(void);

class UI_Button : public sf::Drawable {
    sf::Text btnText;
    sf::RectangleShape btnField;
    bool isActive;
    bool isFocused = false;
    bool isPressed = false;
    bool isVisible;
    bool keepActive = false;
    buttonHandlerFunction handlerFunction = nullptr;


public:
    UI_Button();
    UI_Button(const sf::Text& text, const sf::Vector2f& size, bool isActive = false, bool isVisible = true);
    virtual ~UI_Button();

    virtual void HandleMouseMoveEvent(const sf::Event::MouseMoveEvent &e);
    virtual void HandleMouseButtonPressedEvent(const sf::Event::MouseButtonEvent &e);
    virtual void HandleMouseButtonReleasedEvent(const sf::Event::MouseButtonEvent &e);

    bool IsActive();
    void Deactivate();
    void SetHandlerFunction(const buttonHandlerFunction & handlerFunction, bool shouldKeepActive = false);
    void SetFillColor(const sf::Color &color);
    void SetSize(const sf::Vector2f &size);
    void SetTexture(const sf::Texture * texture, bool resetRect = false);
    void SetText(const char * string, const sf::Font& font, unsigned int characterSize = 30);
    void SetOrigin(const sf::Vector2f &origin);
    void SetPosition(const sf::Vector2f &position);
    // sf::Vector2f GetOrigin(); TODO: implement later; this function may be useful
    // sf::Vector2f GetPosition(); TODO: implement later; this function may be useful
    // void Move(float offsetX, float offsetY); TODO: implement later; this function may be useful
    // void Move(const sf::Vector2f &offset); TODO: implement later; this function may be useful
    sf::FloatRect GetLocalBounds();
    sf::FloatRect GetGlobalBounds();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(btnField, states);
        if(isPressed){
            sf::RectangleShape pressedFilter(btnField.getSize());
            pressedFilter.setOrigin(btnField.getOrigin());
            pressedFilter.setPosition(btnField.getPosition());
            pressedFilter.setFillColor(sf::Color(0, 0, 0, 50));
            target.draw(pressedFilter, states);
        }

        target.draw(btnText, states);
    }
};


#endif //PROJECT_ZOMBIE_SHOOTER_BUTTON_H
