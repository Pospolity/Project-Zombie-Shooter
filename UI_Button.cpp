//
// Created on 07/05/2018.
//

#include "UI_Button.h"
//#include "iostream"

UI_Button::UI_Button() :
        btnText(),
        btnField() {}

UI_Button::UI_Button(const sf::Text& text, const sf::Vector2f& size, bool isActive, bool isVisible) :
        btnText(text),
        btnField(sf::RectangleShape(size)),
        isActive(isActive),
        isVisible(isVisible) {

    // set text origin to center of the text and set position to the center of the button
    sf::FloatRect btnTextRect = btnText.getLocalBounds();
    btnText.setOrigin(btnTextRect.left + btnTextRect.width / 2.0f, btnTextRect.top + btnTextRect.height / 2.0f);
    sf::FloatRect btnFieldRect = this->GetGlobalBounds();
    btnText.setPosition(btnFieldRect.left + btnFieldRect.width / 2.0f, btnFieldRect.top + btnFieldRect.height / 2.0f);
}

UI_Button::~UI_Button() {}

void UI_Button::HandleMouseMoveEvent(const sf::Event::MouseMoveEvent &e) {
    sf::FloatRect btnFieldRect = btnField.getGlobalBounds();
    bool isMouseInside = true;
    if (e.x < btnFieldRect.left)
        isMouseInside = false;
    else if (e.x > btnFieldRect.left + btnFieldRect.width)
        isMouseInside = false;
    else if (e.y < btnFieldRect.top)
        isMouseInside = false;
    else if (e.y > btnFieldRect.top + btnFieldRect.height)
        isMouseInside = false;

    isFocused = isMouseInside;
}

void UI_Button::HandleMouseButtonPressedEvent(const sf::Event::MouseButtonEvent &e){
    if(isFocused && e.button == sf::Mouse::Left)
        isPressed = true;
}

void UI_Button::HandleMouseButtonReleasedEvent(const sf::Event::MouseButtonEvent &e){
    if(isFocused && isPressed && e.button == sf::Mouse::Left){

        isActive = true;

        if(handlerFunction)
        handlerFunction();

        if(!keepActive)
            Deactivate();
    }
    isPressed = false;
}

bool UI_Button::IsActive() {
    return isActive;
}

void UI_Button::Deactivate() {
    isActive = false;
}

void UI_Button::SetHandlerFunction(const buttonHandlerFunction & handlerFunction, bool shouldKeepActive) {
    this->handlerFunction = handlerFunction;
    this->keepActive = shouldKeepActive;
}

void UI_Button::SetFillColor(const sf::Color &color) {
    btnField.setFillColor(color);
}

void UI_Button::SetSize(const sf::Vector2f &size) {
    btnField.setSize(size);

    // update text position
    sf::FloatRect btnRect = this->GetGlobalBounds();
    btnText.setPosition(btnRect.left + btnRect.width / 2.0f, btnRect.top + btnRect.height / 2.0f);
}

void UI_Button::SetText(const char *string, const sf::Font &font, unsigned int characterSize) {
    btnText.setString(string);
    btnText.setFont(font);
    btnText.setCharacterSize(characterSize);
    // update text origin and position
    sf::FloatRect btnTextRect = btnText.getLocalBounds();
    btnText.setOrigin(btnTextRect.left + btnTextRect.width / 2.0f, btnTextRect.top + btnTextRect.height / 2.0f);
    sf::FloatRect btnRect = this->GetGlobalBounds();
    btnText.setPosition(btnRect.left + btnRect.width / 2.0f, btnRect.top + btnRect.height / 2.0f);
}

void UI_Button::SetTexture(const sf::Texture *texture, bool resetRect) {
    btnField.setTexture(texture, resetRect);
}

sf::FloatRect UI_Button::GetLocalBounds() {
    return btnField.getLocalBounds();
}

sf::FloatRect UI_Button::GetGlobalBounds() {
    return btnField.getGlobalBounds();
}

void UI_Button::SetOrigin(const sf::Vector2f &origin) {
    btnField.setOrigin(origin);
}

void UI_Button::SetPosition(const sf::Vector2f &position) {
    btnField.setPosition(position);
    sf::FloatRect btnRect = this->GetGlobalBounds();
    btnText.setPosition(btnRect.left + btnRect.width / 2.0f, btnRect.top + btnRect.height / 2.0f);
}

