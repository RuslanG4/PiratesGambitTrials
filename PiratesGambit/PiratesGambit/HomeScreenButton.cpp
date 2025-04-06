#include "HomeScreenButton.h"

HomeScreenButton::HomeScreenButton(const sf::Vector2f& position, std::string _string) : Button()
{
	button.setScale(4.5f, 2.5f);
	button.setPosition(position);
	text.setString(_string);
	text.setCharacterSize(80);
	text.setFillColor(sf::Color(220, 235, 241));
	text.setOutlineColor(sf::Color(12, 42, 61));
	text.setOutlineThickness(10.f);
	centerText(text);
}

void HomeScreenButton::handleEvent(const sf::Event& event)
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
