#pragma once
#include"Includes.h"

class Button
{
public:
    Button(const sf::Vector2f& position, std::string _string);

    void handleEvent(const sf::Event& event);
    void draw(const std::unique_ptr<sf::RenderWindow>& window);
    bool isClicked() const { return clicked; }

    void centerText(sf::Text& _text);

private:
    sf::Sprite button;
    sf::Text text;
    bool clicked;
};
