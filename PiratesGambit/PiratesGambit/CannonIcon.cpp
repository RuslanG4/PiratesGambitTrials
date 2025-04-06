#include "CannonIcon.h"

void CannonIcon::Update(float _dt)
{
	Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 1, 0, _dt);
}
