#include "PirateUnit.h"

#include "DamageCalculations.h"

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

void PirateUnit::Attack(sf::Vector2f _targetDirection)
{
	currentState = ATTACK;
	animationState.currentFrame = 0;
	animationState.elapsedTime = 0;

	targetPosition = _targetDirection;
}

void PirateUnit::TakeDamage(int _totalDamage)
{
	std::cout << "Current stack : " << unitStats.stackSize << " Current health : " << unitStats.health << "\n";


	std::cout << "damage : " << _totalDamage << "\n";
	while(_totalDamage != 0)
	{
		if(_totalDamage - unitBaseStats.health >= 0)
		{
			unitStats.stackSize--;
			std::cout << "new stack (-10) : " << unitStats.stackSize << "\n";
			_totalDamage -= unitBaseStats.health;
		}else
		{
			unitStats.health -= _totalDamage;
			std::cout  << "new health : " << unitStats.health << "\n";
			if(unitStats.health <= 0)
			{
				unitStats.health = unitBaseStats.health + unitStats.health;
				unitStats.stackSize--;
			}
			_totalDamage = 0;
		}
		if (unitStats.stackSize <= 0)
		{
			currentState = DEATH;
			animationState.currentFrame = 0;
			animationState.elapsedTime = 0;
			return;
		}
	}

	std::cout << "End stack : " << unitStats.stackSize<< " End health : " << unitStats.health <<"\n";

	// Update the displayed stack size
	unitAmount.updateAmount(unitStats.stackSize);
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
