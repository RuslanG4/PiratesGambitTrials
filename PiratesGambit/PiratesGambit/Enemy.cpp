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
		//myHitbox->render(window);
		//for (auto& node : updateableArea->getUpdateableNodes())
		//{
		//	if (node != nullptr) {
		//		window->draw(*(node->debugShape));
		//	}
		//}
	}
}

void Enemy::MoveUnit(const std::vector<std::shared_ptr<Node>>& _grid)
{
	if (!path.empty()) {
		sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - body.getPosition();
		float magnitude = Utility::magnitude(distance.x, distance.y);

		if (magnitude < 2.0f) {
			currentNodeInPath++;

			if(currentNodeInPath >= path.size())
			{
				path.clear();
				return;
			}

			distance = path[currentNodeInPath]->getMidPoint() - body.getPosition();
		}

		distance = Utility::unitVector2D(distance);

		body.setPosition(body.getPosition() + distance * 1.f); //2.f is speed
		myHitbox->setPosition(body.getPosition());
		if (Utility::magnitude(distance.x, distance.y) <= 0 && currentState != ATTACK) {
			currentState = IDLE;
		}else
		{
			currentState = WALK;
		}
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

void Enemy::updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const
{
	updateableArea->updateVisibleNodes(_startNode, depth);
}

void Enemy::PassPath(const std::vector<std::shared_ptr<Node>>& _path)
{
	path.clear();
	path = _path;

	currentNodeInPath = 0;
}


