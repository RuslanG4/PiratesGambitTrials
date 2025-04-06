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
	}
	enemyUI->Render(window);

	//myHitbox->render(window);

	//for (auto& node : updateableArea->getUpdateableNodes())
	//	{
	//		if (node != nullptr) {
	//			window->draw(*(node->debugShape));
	//		}
	//	}
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

sf::FloatRect Enemy::GetGlobalBounds() const
{
	if(isOnBoat())
	{
		return boatRef->GetGlobalBounds();
	}else
	{
		return myHitbox->GetGlobalBounds();
	}
}

void Enemy::SetPosition(sf::Vector2f _pos)
{
	if (isOnBoat())
	{
		boatRef->RotateTowardsPlayer(_pos - body.getPosition());
		boatRef->setPosition(_pos);
	}
	body.setPosition(_pos);
	myHitbox->setPosition(_pos);
	enemyUI->setPosition(sf::Vector2f(_pos.x - 50, _pos.y - 20));
}

void Enemy::updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const
{
	updateableArea->updateVisibleNodes(_startNode, depth);
}

void Enemy::FaceDirection(sf::Vector2f _pos)
{
	if (_pos.x < 0)
	{
		FacePlayer(-2);
	}
	else
	{
		FacePlayer(2);
	}
}

void Enemy::UpdateDirection(sf::Vector2f _direction)
{
	if (std::abs(_direction.x) > std::abs(_direction.y)) {
		currentDirection = (_direction.x > 0) ? EAST : WEST;
	}
	else {
		currentDirection = (_direction.y > 0) ? SOUTH : NORTH;
	}
}

void Enemy::boardBoat(const std::shared_ptr<EnemyBoat>& _boat)
{
	body.setPosition(_boat->getPosition());
	myHitbox->setPosition(_boat->getPosition());
	enemyUI->setPosition(sf::Vector2f(_boat->getPosition().x - 50, _boat->getPosition().y - 20));
	onBoat = true;
	boatRef = _boat;
}

void Enemy::disembarkBoat(const std::shared_ptr<Node>& _node)
{
	onBoat = false;
	body.setPosition(_node->getMidPoint());
	boatRef->setDockedNode(_node);
}

void Enemy::LoseArmy()
{
	float lossPercent = 0.1f; // 10% loss
	for (auto& unit : army->getArmy())
	{
		unit->setStackSize(std::round(unit->getStackSize() - (unit->getStackSize() * lossPercent))); //round up
	}
}

void Enemy::ChangeState(EnemyState* newState)
{
	if (currentState)
		currentActionState->Exit(*this);

	currentActionState = newState;

	if (currentActionState)
		currentActionState->Enter(*this);
}

void Enemy::setFactionAllegiance()
{
	switch (enemyAllegiance)
	{
	case YELLOW_PLAYER:
		factionAllegiance = "Yellow";
		break;
	case RED_PLAYER:
		factionAllegiance = "Red";
		break;
	case BLUE_PLAYER:
		factionAllegiance = "Blue";
		break;
	case GREEN_PLAYER:
		factionAllegiance = "Green";
		break;
	case BLACK_PLAYER:
		factionAllegiance = "Black";
		break;
	}
}

std::string Enemy::GetEnemyAllegiance() const
{
	switch(enemyAllegiance)
	{
	case YELLOW_PLAYER:
		return "Yellow";
	case RED_PLAYER:
		return "Red";
	case BLUE_PLAYER:
		return "Blue";
	case GREEN_PLAYER:
		return "Green";
	case BLACK_PLAYER:
		return "Black";
	default:
		return "Unknown";
	}

}

void Enemy::updateEnemyAllegiance(const int& _value)
{
	playerAllegiance.changeAllegiance(_value);
	enemyUI->updateAllegiance(playerAllegiance);
}


