#include "PirateUnit.h"

void PirateUnit::updateUnitAmount(int _amount)
{
	unitAmount.updateAmount(_amount);
}

void PirateUnit::placeUnitAmountText()
{
	sf::Vector2f position = { sprite.getPosition().x - 32, sprite.getPosition().y + 14 };
	unitAmount.setPosition(position);
}

void PirateUnit::moveUnit(sf::Vector2f _vel)
{
	velocity = _vel;
	sprite.setPosition(sprite.getPosition() + _vel * 2.f);
	placeUnitAmountText();
	if (Utility::magnitude(velocity.x, velocity.y) <= 0 && currentState != ATTACK) {
		currentState = IDLE;
	}
}

void PirateUnit::Attack()
{
	currentState = ATTACK;
	animationState.currentFrame = 0;
	animationState.elapsedTime = 0;
}

void PirateUnit::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(sprite);
	unitAmount.render(window);
}

void PirateUnit::placeUnit(sf::Vector2f _pos)
{
	sprite.setPosition(_pos);
	placeUnitAmountText();
}
