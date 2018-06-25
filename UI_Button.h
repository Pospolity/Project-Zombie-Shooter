//
// Created on 07/05/2018.
//

// INFO:
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
#include "colorPalette.h"

const int DEFAULT_BTN_FONT_SIZE = 30;
const float DEFAULT_BTN_HOVERED_TEXT_THICKENING = 1.15;

typedef std::function<void()> buttonTriggerFunction;

void doNothing();

enum class OriginPosition {
    TOP_LEFT, MIDDLE
};

class UI_Button : public sf::Drawable {

public:
    UI_Button();
    UI_Button(const sf::Text& text, const sf::Vector2f& size, bool isActive = false, bool keepActive = false, bool isVisible = true, bool isEnabled = true);
    virtual ~UI_Button();

    virtual void Update(const sf::Vector2f &mousePosition);

    void OnPressedTriggerFunction(buttonTriggerFunction &function) {this->onPressed = function;};
    void OnReleasedTriggerFunction(buttonTriggerFunction &function) {this->onReleased = function;};

    bool IsActive(){ return isActive; };
    void Deactivate(){ isActive = false; };
    void Show() { isVisible = true; };
    void Hide() { isVisible = false; };
    void Enable() { isEnabled = true; };
    void Disable() { isEnabled = false; };
    void SetFillColor(const sf::Color &color);
    void SetOutlineColor(const sf::Color &color);
    void SetOutlineThickness(float thickness);
    void SetSize(const sf::Vector2f &size);
    void SetTexture(const sf::Texture * texture, bool resetRect = false);
    void SetTextureRect(const sf::IntRect& rect);
    void SetText(const char * string, const sf::Font& font, unsigned int characterSize = DEFAULT_BTN_FONT_SIZE);
    void SetOrigin(const sf::Vector2f &origin);
    void SetOrigin(const OriginPosition originPosition);
    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float angle);
    // sf::Vector2f GetOrigin(); TODO: implement later; this function may be useful
    // sf::Vector2f GetPosition(); TODO: implement later; this function may be useful
    // void Move(float offsetX, float offsetY); TODO: implement later; this function may be useful
    // void Move(const sf::Vector2f &offset); TODO: implement later; this function may be useful
    sf::FloatRect GetLocalBounds();
    sf::FloatRect GetGlobalBounds();
    sf::Color GetFillColor();
    sf::Vector2f GetSize();
    float GetRotation();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

        if (!isVisible)
            return;

        target.draw(btnField, states);

        if(isEnabled){

            if(isPressed || isActive){
                sf::RectangleShape pressedOrActiveFilter(btnField.getSize());
                pressedOrActiveFilter.setOrigin(btnField.getOrigin());
                pressedOrActiveFilter.setPosition(btnField.getPosition());
                pressedOrActiveFilter.setFillColor(DEFAULT_BTN_PRESSED_OR_ACTIVE_FILTER_COLOR);
                target.draw(pressedOrActiveFilter, states);
            }

            if(isHovered){
                sf::Text btnTextHovered(btnText);
                btnTextHovered.setOutlineThickness(DEFAULT_BTN_HOVERED_TEXT_THICKENING);
                btnTextHovered.setOutlineColor(btnTextHovered.getFillColor());
                target.draw(btnTextHovered, states);
            } else
                target.draw(btnText, states);

        } else {

            sf::RectangleShape disabledFilter(btnField.getSize());
            disabledFilter.setOrigin(btnField.getOrigin());
            disabledFilter.setPosition(btnField.getPosition());
            disabledFilter.setFillColor(DEFAULT_BTN_DISABLED_FILTER_COLOR);
            disabledFilter.setTexture(btnField.getTexture());
            target.draw(disabledFilter);

            target.draw(btnText, states);
        }
    }

    void applyDefaultStyle();

private:
    virtual void handleMouse(const sf::Vector2f &mousePosition);
    void handleMouseMove(const sf::Vector2f &mousePosition);

    sf::Text btnText;
    sf::RectangleShape btnField;

    bool isActive;
    bool isHovered = false;
    bool isPressed = false;
    bool isVisible;
    bool isEnabled;
    bool keepActive;

    // functions triggered on events
    std::function<void()> onPressed = doNothing;
    std::function<void()> onReleased = doNothing;
    //std::function<void()> *onHovered; TODO: implement later; this function may be useful
    //std::function<void()> *onLeaved; TODO: implement later; this function may be useful

};


#endif //PROJECT_ZOMBIE_SHOOTER_BUTTON_H