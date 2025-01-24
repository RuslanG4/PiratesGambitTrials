#pragma once
#include "Projectile.h"

class CannonBall : public Projectile
{
public:
	CannonBall(sf::Vector2f _pos, sf::Vector2f _vel = {0,0});

	void init() override;
private:
};

