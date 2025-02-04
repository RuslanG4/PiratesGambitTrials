#include "Enemy.h"
#include "Boat.h"


void Enemy::update(double dt)
{
	handleAnimationStates(dt);
}

void Enemy::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	if (!onBoat)
	{
		window->draw(body);
	}
}

void Enemy::handleAnimationStates(double dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(body, animationState, idleAnimation, 4, 0, dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(body, animationState, walkAnimation, 6, 1, dt);
		break;
	}
}
