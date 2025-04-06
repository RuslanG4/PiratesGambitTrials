#pragma once
#include"Includes.h"
#include"Mouse.h"
class Button
{
public:
    Button();

    virtual void handleEvent(const sf::Event& event) = 0;

    void SetPosition(sf::Vector2f _pos);
    void draw(const std::unique_ptr<sf::RenderWindow>& window);
    bool isClicked() const { return clicked; }
    void centerText(sf::Text& _text);

protected:
    sf::Sprite button;
    sf::Text text;
    bool clicked;
};
