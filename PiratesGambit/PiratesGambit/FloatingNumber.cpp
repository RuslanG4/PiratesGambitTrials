#include "FloatingNumber.h"

FloatingNumber::FloatingNumber(sf::Vector2f _pos, int _value)
{
	text.setFont(TextureManager::getInstance().getFont("Varsity"));
	text.setCharacterSize(40);
	text.setPosition(_pos);
	if (_value == 0) {
		text.setString("");
	}else
		text.setString(std::to_string(_value));
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setFillColor(sf::Color::White);
	lifetime = 0;
	lifeTimeClock.restart();
}

void FloatingNumber::update(float deltaTime)
{
	lifetime += deltaTime / 1000.0f;
	text.setPosition(text.getPosition().x, text.getPosition().y - 2);
	text.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 - (lifetime * 255))));
    text.setOutlineColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(255 - (lifetime * 255))));
	if (lifetime >= 1)
	{
		text.setString("");
		markedForDelete = true;
	}
}

void FloatingNumber::render(const std::unique_ptr<sf::RenderWindow>& _window)
{
	if (text.getString() != "")
	{
		_window->draw(text);
	}
}
