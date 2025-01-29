#include "BuccaneerIcon.h"

void BuccaneerIcon::Update(float _dt)
{
	Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 4, 0, _dt);
}
