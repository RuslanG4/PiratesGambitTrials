#include "Boat.h"
#include"Player.h"

void Boat::processKeys(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::Space)
	{
		fireCannonBall(1);
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
	myHitbox->render(window);
	for (auto& cannonball : cannonBalls) {
		cannonball->render(window);
	}
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

		for (auto& cannonball : cannonBalls) {
			cannonball->update();
		}
	}
}

bool Boat::checkCollision(const std::shared_ptr<Node>& _node, sf::Vector2f& _pos)
{
	if (_node->getIsLand()) {
		if (Utility::collisionWithPoint(myHitbox->getPosition() + _pos, _node->getPosition(), sf::Vector2f(_node->getSize(), _node->getSize())))
		{
			controller->deflect();
			boatSprite.setPosition(controller->getPosition());
			myHitbox->setPosition(controller->getPosition());
			return true;
		}
	}
	return false;
}

void Boat::addCannonBall()
{
	cannonBalls.push_back(std::make_shared<CannonBall>(sf::Vector2f(-100, -100)));
}

void Boat::fireCannonBall(int _direction)
{
	float angleRadians = controller->getRotation() * Utility::DEG_TO_RADIAN;

	float forwardX = std::cos(angleRadians);
	float forwardY = std::sin(angleRadians);

	sf::Vector2f velocity;
	if(_direction == 1)
	{
		velocity = { -forwardY, forwardX };
	}
	else
	{
		velocity = { forwardY, -forwardX };
	}
	
	for (auto& cannonball : cannonBalls) {
		if (!cannonball->getIsActive()) {

			cannonball->fire(controller->getPosition(), velocity);
			break;
		}
	}
}
