#include "Boat.h"
#include"Player.h"

void Boat::processKeys(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::Q) {
		fireDirection = 0;
		fireIndicator.setScale(0.5, 0.5);
	}
	if (t_event.key.code == sf::Keyboard::E) {
		fireDirection = 1;
		fireIndicator.setScale(0.5, -0.5);
	}
	if (t_event.key.code == sf::Keyboard::Space)
	{
		fireCannonBall(fireDirection);
		canShoot = false;
	}
}

void Boat::processKeyUp(sf::Event t_event)
{
	canShoot = true;
}

void Boat::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(boatSprite);
	window->draw(fireIndicator);
	//myHitbox->render(window);
}

void Boat::update(double dt)
{
	sf::Vector2f desiredPosition = controller->move(dt);

	for (auto& node : currentPlayer->getUpdateableArea()->getUpdateableNodes())
	{
		if (checkCollision(node, desiredPosition))
		{
			//currentPlayer->disembarkBoat(node);
			break;
		}
	}
	if (currentPlayer->isOnBoat()) {
		controller->setCurrentPosition(controller->getPosition() + desiredPosition);
		controller->update_speed();

		currentPlayer->getPlayerController()->setCurrentPosition(controller->getPosition() + desiredPosition);

		boatSprite.setPosition(controller->getPosition());
		boatSprite.setRotation(controller->getRotation());

		myHitbox->setPosition(controller->getPosition());
		myHitbox->setRotation(controller->getRotation());
	}
	updateIndicator();
}

bool Boat::checkCollision(const std::shared_ptr<Node>& _node, sf::Vector2f& _pos)
{
	if (_node->getIsLand()) {
		if (Utility::collisionWithPoint(myHitbox->getPosition() + _pos, _node->getPosition(), sf::Vector2f(_node->getNodeData().size, _node->getNodeData().size)))
		{
			controller->deflect();
			boatSprite.setPosition(controller->getPosition());
			myHitbox->setPosition(controller->getPosition());
			return true;
		}
	}
	return false;
}

void Boat::fireCannonBall(int _direction)
{
	auto item = currentPlayer->getInventory()->getItem(CANNONBALLS);
		if (item != nullptr) {
			if (item->getStackSize() > 0) {
				float angleRadians = controller->getRotation() * Utility::DEG_TO_RADIAN;

				float forwardX = std::cos(angleRadians);
				float forwardY = std::sin(angleRadians);

				sf::Vector2f velocity;
				if (_direction == 1)
				{
					velocity = { -forwardY, forwardX };
				}
				else
				{
					velocity = { forwardY, -forwardX };
				}
		
				BulletFactory::getInstance().createCannonBall(fireIndicator.getPosition(), Utility::unitVector2D(velocity) * 0.5f, 0.85f);

				currentPlayer->getInventory()->removeItemFromStack(CANNONBALLS);
				ParticleManager::getInstance().CreateShootParticle(fireIndicator.getPosition());
			}
		}
}

void Boat::updateIndicator()
{
	sf::Vector2f shipPos = controller->getPosition();
	float shipRotation = controller->getRotation();

	sf::Vector2f localOffset = (fireDirection == 1) ? sf::Vector2f(0.f, 30.f) : sf::Vector2f(0.f, -30.f);

	float radians = shipRotation * Utility::DEG_TO_RADIAN;

	sf::Vector2f rotatedOffset;
	rotatedOffset.x = localOffset.x * std::cos(radians) - localOffset.y * std::sin(radians);
	rotatedOffset.y = localOffset.x * std::sin(radians) + localOffset.y * std::cos(radians);

	fireIndicator.setPosition(shipPos + rotatedOffset);

	fireIndicator.setRotation(shipRotation);
}
