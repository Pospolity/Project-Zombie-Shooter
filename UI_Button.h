//
// Created on 07/05/2018.
//

/// INFO:
//
// Buttons remain in state pressed/active until next Update() call.
// Setting keepActive to true makes button remain in state active until Deactivate() call;
//

#ifndef PROJECT_ZOMBIE_SHOOTER_BUTTON_H
#define PROJECT_ZOMBIE_SHOOTER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "MainResources.h"
#include <functional>

const sf::Color DEFAULT_BTN_PRESSED_FILTER_COLOR(0, 0, 0, 50);
const int DEFAULT_BTN_FONT_SIZE = 30;

void doNothing();

enum class OriginPosition {
    TOP_LEFT, MIDDLE
};

class UI_Button : public sf::Drawable {

public:
    UI_Button();
    UI_Button(const sf::Text& text, const sf::Vector2f& size, bool isActive = false, bool keepActive = false, bool isVisible = true);
    virtual ~UI_Button();

    virtual void Update(const sf::Vector2f &mousePosition);

    void OnPressedTriggerFunction(std::function<void()> &function) {this->onPressed = function;};
    void OnReleasedTriggerFunction(std::function<void()> &function) {this->onReleased = function;};

    bool IsActive();
    void Deactivate();
    void SetFillColor(const sf::Color &color);
    void SetSize(const sf::Vector2f &size);
    void SetTexture(const sf::Texture * texture, bool resetRect = false);
    void SetText(const char * string, const sf::Font& font, unsigned int characterSize = DEFAULT_BTN_FONT_SIZE);
    void SetOrigin(const sf::Vector2f &origin);
    void SetOrigin(const OriginPosition originPosition);
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
            pressedFilter.setFillColor(DEFAULT_BTN_PRESSED_FILTER_COLOR);
            target.draw(pressedFilter, states);
        }

        if(isHovered){
            sf::Text btnTextHovered(btnText);
            btnTextHovered.setOutlineThickness(1.15);
            btnTextHovered.setOutlineColor(btnTextHovered.getFillColor());
            //btnTextHovered.setStyle(sf::Text::Underlined);
            //btnTextHovered.setFillColor(btnTextHovered.getFillColor() - sf::Color(255, 255, 255, 0));
            target.draw(btnTextHovered, states);
        } else
            target.draw(btnText, states);
    }

private:
    virtual void handleMouse(const sf::Vector2f &mousePosition);
    void handleMouseMove(const sf::Vector2f &mousePosition);

    sf::Text btnText;
    sf::RectangleShape btnField;

    bool isActive;
    bool isHovered = false;
    bool isPressed = false;
    bool isVisible;
    bool keepActive;

    // functions triggered on events
    std::function<void()> onPressed = doNothing;
    std::function<void()> onReleased = doNothing;
    //std::function<void()> *onHovered; TODO: implement later; this function may be useful
    //std::function<void()> *onLeaved; TODO: implement later; this function may be useful

};


#endif //PROJECT_ZOMBIE_SHOOTER_BUTTON_H