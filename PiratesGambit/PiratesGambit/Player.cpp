#include "Player.h"

#include "Boat.h"

void Player::update(double dt)
{
	bool collision = false;
	sf::Vector2f desiredPosition = controller->move(dt); //next position prediction

	for (auto& node : updateableArea->getUpdateableNodes())
	{
		if (checkCollision(node, desiredPosition))
		{
			collision = true;
			break;
		}

	}
	if (!collision) {
		controller->setCurrentPosition(controller->getPosition() + desiredPosition); //set positions
		myHitbox->setPosition(controller->getPosition());
		body.setPosition(controller->getPosition());

		if (controller->getVelocity().x < 0) //sprite facing direction
		{
			body.setScale(-2, 2);
		}
		else if (controller->getVelocity().x > 0)
		{
			body.setScale(2, 2);
		}
		
	}

	updatePlayerState(); //animation
	handlePlayerStates(dt);
}

void Player::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	if (!onBoat)
	{
		window->draw(body);
		//myHitbox->render(window);
	}

	//debug
	//for (auto& node : updateableArea->getUpdateableNodes())
	//{
	//	if (node != nullptr) {
	//		window->draw(*(node->debugShape));
	//	}
	//}
}

/// <summary>
/// handles the state of player for animation and updates
/// </summary>
void Player::handlePlayerStates(double dt)
{
	switch(currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(body, animationState,idleAnimation, 4, 0,dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(body, animationState,walkAnimation, 6, 1,dt);
		break;
	}
}

///<summary>
/// determines players state based on movement
///</summary>
void Player::updatePlayerState()
{
	if(Utility::magnitude(controller->getVelocity().x, controller->getVelocity().y) > 0.2f){
		currentState = WALK;
	}
	else
	{
		currentState = IDLE;
	}
}

/// <summary>
/// updates local area 
/// </summary>
/// <param name="_startNode">current node</param>
/// <param name="depth">how wide area</param>
void Player::updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const
{
	updateableArea->updateVisibleNodes(_startNode, depth);
}

///<summary>
/// Collision check with land
///</summary>
bool Player::checkCollision(const std::shared_ptr<Node>& _node, sf::Vector2f& _pos)
{
	if (!_node->getIsLand())
	{
		if (Utility::collisionWithNode(myHitbox->getTopLeftCorner() + _pos, myHitbox->getSize(), _node->getPosition(), _node->getNodeData().size))
		{
			controller->deflect(); //put player back
			myHitbox->setPosition(controller->getPosition());
			return true;
		}
	}
	return false;
}

///<summary>
/// set boat to change movement and updates
///</summary>
void Player::boardBoat(const std::shared_ptr<Boat>& _boat)
{
	onBoat = true;
	currentBoat = _boat;
	controller->setCurrentPosition(currentBoat.lock()->getController()->getPosition());
}

/// <summary>
/// leave current boat
/// </summary>
/// <param name="_node">position to drop player sprite</param>
void Player::disembarkBoat(const std::shared_ptr<Node>& _node)
{
	onBoat = false;
	currentBoat.reset();

	controller->setCurrentPosition(_node->getMidPoint());
	myHitbox->setPosition(controller->getPosition());
	body.setPosition(controller->getPosition());
}


