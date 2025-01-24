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
	void AnimateShoot(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, bool& _bulletFrame, int _bulletFrameNumber, int _colAmt, int _rowNum, float _dt);
	void AnimateDeath(sf::Sprite& _sprite, int _colNum, int _rowNum);

	void AnimateParticle(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, int _colNum, int _rowNum, int _width, int _height, float _dt);

	Animator(Animator const&) = delete;
private:
	Animator()
	{

	};
	float animateTime{0};
	int currentFrame{ 0 };
};

