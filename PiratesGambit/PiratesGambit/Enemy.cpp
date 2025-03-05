#include "Enemy.h"
#include "EnemyBoat.h"


void Enemy::update(double dt)
{
	handleAnimationStates(dt);
	if (currentActionState)
		currentActionState->Update(*this, dt);
}

void Enemy::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	if (!onBoat)
	{
		window->draw(body);
		//myHitbox->render(window);
		//for (auto& node : updateableArea->getUpdateableNodes())
		//{
		//	if (node != nullptr) {
		//		window->draw(*(node->debugShape));
		//	}
		//}
	}else
	{
		boatRef->render(window);
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

void Enemy::updatePosition(const sf::Vector2f& _pos)
{
	body.setPosition(_pos);
	myHitbox->setPosition(_pos);
}

void Enemy::SetPosition(sf::Vector2f _pos)
{
	if (!onBoat) {
		body.setPosition(_pos);
	} else
	{
		boatRef->setPosition(_pos);
	}
	myHitbox->setPosition(_pos);
}

void Enemy::updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const
{
	updateableArea->updateVisibleNodes(_startNode, depth);
}

void Enemy::boardBoat(const std::shared_ptr<EnemyBoat>& _boat)
{
	onBoat = true;
	boatRef = _boat;
}

void Enemy::disembarkBoat(const std::shared_ptr<Node>& _node)
{
	onBoat = false;
	body.setPosition(_node->getMidPoint());
}

void Enemy::ChangeState(EnemyState* newState)
{
	if (currentState)
		currentActionState->Exit(*this);

	currentActionState = newState;

	if (currentActionState)
		currentActionState->Enter(*this);
}


