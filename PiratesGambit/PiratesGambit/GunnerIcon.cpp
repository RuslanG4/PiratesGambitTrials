#include "GunnerIcon.h"

void GunnerIcon::Update(float _dt)
{
	Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 4, 0, _dt);
}
