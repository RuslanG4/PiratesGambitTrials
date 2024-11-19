#include "Player.h"
#include "Boat.h"

void Player::update(double dt)
{
	bool temmp = false;
	sf::Vector2f desiredPosition = controller->move(dt);

	for (auto& node : updateableArea.getUpdateableNodes())
	{
		if (checkCollision(node, desiredPosition))
		{
			temmp = true;
			break;
		}

	}
	if (!temmp) {
		controller->setCurrentPosition(controller->getPosition() + desiredPosition);

		myHitbox->setPosition(controller->getPosition());
		body.setPosition(controller->getPosition());
		
	}
	updatePlayerState();
	handlePlayerStates();
}

void Player::render(sf::RenderWindow& window) const
{
	if (!onBoat)
	{
		window.draw(body);
		myHitbox->render(window);
	}
	for (Node* node : updateableArea.getUpdateableNodes())
	{
		if (node != nullptr) {
			window.draw(*(node->debugShape));
		}
	}
}

void Player::handlePlayerStates()
{
	switch(currentState)
	{
	case IDLE:
		animatePlayer(4,0);
		break;
	case WALK:
		animatePlayer(6, 1);
		break;
	}
}

void Player::animatePlayer(int _colAmt, int _rowNum)
{
	animateTime++;
	if (animateTime > 12)//5 is the speed at how fast they animate
	{
		currentFrame++;
		if (currentFrame > _colAmt - 1) //frame 6 is the last frame the robot is running
		{
			currentFrame = 0;

		}
		animateTime = 0;
	}
	int col = currentFrame % _colAmt; //total cols is 5
	int row = _rowNum; //row 0

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	body.setTextureRect(rectSourceSprite);
}

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

void Player::updateUpdateableArea(Node*& _startNode, int depth)
{
	updateableArea.updateVisibleNodes(_startNode, depth);
}

bool Player::checkCollision(Node*& _node, sf::Vector2f& _pos)
{
	if (!_node->getIsLand())
	{
		if (Utility::collisionWithNode(myHitbox->getTopLeftCorner() + _pos, myHitbox->getSize(), _node->getPosition(), _node->getSize()))
		{
			controller->deflect();
			myHitbox->setPosition(controller->getPosition());
			return true;
		}
	}
	return false;
}

void Player::boardBoat(std::shared_ptr<Boat>& _boat)
{
	onBoat = true;
	currentBoat = _boat;
	controller->setCurrentPosition(currentBoat.lock()->getController()->getPosition());
}

void Player::disembarkBoat(Node*& _node)
{
	onBoat = false;
	currentBoat.reset();

	controller->setCurrentPosition(_node->getMidPoint());
	myHitbox->setPosition(controller->getPosition());
	body.setPosition(controller->getPosition());

}


