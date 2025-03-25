#include "Button.h"

#include "Mouse.h"

Button::Button(const sf::Vector2f& position, std::string _string) : clicked(false)
{
    sf::IntRect textureRect{ 128,0,96,64 };
    button.setTexture(TextureManager::getInstance().getTexture("BUTTONS"));
    button.setTextureRect(textureRect);
    button.setPosition(position);
    button.setOrigin(96 / 2, 64 / 2);
    button.setScale(4.5f, 2.5f);

    text.setFont(TextureManager::getInstance().getFont("Comic"));
    text.setString(_string);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color(220, 235, 241));
    text.setOutlineColor(sf::Color(12, 42, 61));
    text.setOutlineThickness(10.f);
    centerText(text);
}

void Button::handleEvent(const sf::Event& event)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
    bool hovering = button.getGlobalBounds().contains(mousePos);

    if (hovering)
        button.setScale(4.6f, 2.6f);
    else
        button.setScale(4.5f, 2.5f);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && hovering)
        clicked = true;
    else if (event.type == sf::Event::MouseButtonReleased)
        clicked = false;
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
