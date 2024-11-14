#include "Boat.h"

void Boat::deflect(PlayerController* _controller)
{
	if (_controller->getSpeed() != 0)
	{
		boatSprite.setPosition(_controller->getPreviousPosition());
		_controller->setSpeed(0);
	}
}
