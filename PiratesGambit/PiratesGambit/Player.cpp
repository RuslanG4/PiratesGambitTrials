#include "Player.h"

void Player::initCamera()
{
	playerCamera.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	playerCamera.setCenter(body.getPosition());
}

void Player::update(double dt)
{
	controller->updateSpeed();
	handleKeyInput();

	sf::Vector2f desiredPosition = controller->move(dt);

	for (auto& node : updateableArea.getUpdateableNodes())
	{
		if(checkCollision(node, desiredPosition) || boardBoat(node))
		{
			break;
		};

	}
	if(!isOnBoat())
	{
		body.setRotation(controller->getRotation());
		sf::Vector2f temp = controller->getPosition();
		body.setPosition(controller->getPosition());
		playerCamera.setCenter(body.getPosition());
	}else
	{
		currentBoat->setRotation(controller->getRotation());
		currentBoat->setPosition(controller->getPosition());
		playerCamera.setCenter(currentBoat->getPosition());
	}
	
}

void Player::render(sf::RenderWindow& window) const
{
	if(!onBoat)
	{
		window.draw(body);
	}
	for (Node* node : updateableArea.getUpdateableNodes())
	{
		if (node != nullptr) {
			window.draw(*(node->debugShape));
		}
	}
}

void Player::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		controller->increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		controller->decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		controller->decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		controller->increaseRotation();
	}
}

void Player::updateUpdateableArea(Node*& _startNode, int depth)
{
	updateableArea.updateVisibleNodes(_startNode, depth);
}

bool Player::checkCollision(Node*& _node, sf::Vector2f& _pos)
{
	sf::Vector2f nodeExtentedPos = sf::Vector2f(_node->getPosition().x + _node->getSize(), _node->getPosition().y + _node->getSize());
	if (isOnBoat() && _node->getIsLand()) {
		if (Utility::collision(_pos, _node->getPosition(), nodeExtentedPos))
		{
			//controller->deflect();
			currentBoat->setCurrentNodeID(_node->getID());
			exitBoat();
			return true;
		}
	}
	else if (!isOnBoat() && !_node->getIsLand())
	{
		if (Utility::collision(_pos, _node->getPosition(), nodeExtentedPos))
		{
			controller->deflect();
			//myPlayer->exitBoat();
			return true;
		}
	}
	else
	{
		controller->setCurrentPosition(_pos);
		return false;
	}
}

bool Player::boardBoat(Node*& _node)
{
	if (_node->getID() == currentBoat->getCurrentNodeID())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			enterBoat();
			return true;
		}
	}
	return false;
}

void Player::enterBoat()
{
	//currentBoat = _boat;
	controller->setCurrentPosition(currentBoat->getPosition());
	controller->setSpeed(0);
	onBoat = true;
}

void Player::exitBoat()
{
	if (currentBoat) {
		onBoat = false;
	}
}

