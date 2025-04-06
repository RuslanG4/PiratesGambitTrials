#include "BirdIcon.h"

void BirdIcon::Update(float _dt)
{
	Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 5, 3, _dt);
}
