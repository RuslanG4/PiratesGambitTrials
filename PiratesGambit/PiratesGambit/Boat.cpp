#include "Boat.h"
#include"Player.h"

void Boat::render(sf::RenderWindow& window) const
{
	window.draw(boatSprite);
	myHitbox->render(window);
}

void Boat::update(double dt)
{
	sf::Vector2f desiredPosition = controller->move(dt);

	for (auto& node : currentPlayer->getUpdateableArea().getUpdateableNodes())
	{
		if (checkCollision(node, desiredPosition))
		{
			currentPlayer->disembarkBoat(node);
			break;
		}
	}
	if (currentPlayer->isOnBoat()) {
		controller->update_speed();
		controller->setCurrentPosition(desiredPosition);

		currentPlayer->getPlayerController()->setCurrentPosition(desiredPosition);

		boatSprite.setPosition(controller->getPosition());
		boatSprite.setRotation(controller->getRotation());

		myHitbox->setPosition(controller->getPosition());
		myHitbox->setRotation(controller->getRotation());
	}
}

bool Boat::checkCollision(Node*& _node, sf::Vector2f& _pos)
{
	if (_node->getIsLand()) {
		if (Utility::collisionWithNode(myHitbox->getTopLeftCorner(), myHitbox->getSize(), _node->getPosition(), _node->getSize()))
		{
			controller->deflect();
			boatSprite.setPosition(controller->getPosition());
			myHitbox->setPosition(controller->getPosition());
			dockedNode = _node;
			return true;
		}
	}
	return false;
}
