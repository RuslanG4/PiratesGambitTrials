#include "Button.h"

#include "Mouse.h"

Button::Button() : clicked(false)
{
    sf::IntRect textureRect{ 128,0,96,64 };
    button.setTexture(TextureManager::getInstance().getTexture("BUTTONS"));
    button.setTextureRect(textureRect);
    button.setOrigin(96 / 2, 64 / 2);

    text.setFont(TextureManager::getInstance().getFont("Varsity"));
    text.setFillColor(sf::Color(220, 235, 241));
    text.setOutlineColor(sf::Color(12, 42, 61));
    centerText(text);
}

void Button::SetPosition(sf::Vector2f _pos)
{
    button.setPosition(_pos);
}

void Button::draw(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(button);
	window->draw(text);
}

void Button::centerText(sf::Text& _text)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect spriteBounds = button.getGlobalBounds();
    _text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    _text.setPosition(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.height / 2);
}
