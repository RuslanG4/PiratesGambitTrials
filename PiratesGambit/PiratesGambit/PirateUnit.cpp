#include "PirateUnit.h"

void PirateUnit::moveUnit(sf::Vector2f _vel)
{
	velocity = _vel;
	sprite.setPosition(sprite.getPosition() + _vel * 2.f);
}

void PirateUnit::render(sf::RenderWindow& _win) const
{
	_win.draw(sprite);
}
