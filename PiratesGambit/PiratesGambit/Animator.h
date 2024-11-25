#pragma once
#include "Includes.h"

class Animator
{
public:
	static Animator& getInstance() {
		static Animator instance;
		return instance;
	}

	void update(sf::RenderWindow& _win);

	void AnimateSprite(sf::Sprite& _sprite,int _colAmt, int _rowNum);

	Animator(Animator const&) = delete;
private:
	Animator()
	{

	};
	int animateTime{0};
	int currentFrame{ 0 };
};

