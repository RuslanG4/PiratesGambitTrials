#pragma once
#include "Includes.h"
#include "Structs.h"

class Animator
{
public:
	static Animator& getInstance() {
		static Animator instance;
		return instance;
	}

	void AnimateSprite(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete ,int _colAmt, int _rowNum, float _dt);

	Animator(Animator const&) = delete;
private:
	Animator()
	{

	};
	float animateTime{0};
	int currentFrame{ 0 };
};

