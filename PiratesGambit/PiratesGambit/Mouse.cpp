#include "Mouse.h"

void Mouse::update(const std::unique_ptr<sf::RenderWindow>& window)
{
	if(!windowRef)
	{
		windowRef = window.get();
	}
	mousePosition = sf::Mouse::getPosition(*window);
}
