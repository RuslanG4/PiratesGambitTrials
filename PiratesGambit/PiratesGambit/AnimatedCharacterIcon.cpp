#include "AnimatedCharacterIcon.h"

void AnimatedCharacterIcon::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(background);
	_window->draw(sprite);
}
