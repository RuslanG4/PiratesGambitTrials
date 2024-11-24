#include "Mouse.h"

void Mouse::update(sf::RenderWindow& _win)
{
	mousePosition = sf::Mouse::getPosition(_win);
}
