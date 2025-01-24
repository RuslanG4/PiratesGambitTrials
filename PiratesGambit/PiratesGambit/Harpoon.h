#pragma once
#include "Projectile.h"

class Harpoon : public Projectile
{
public:
	Harpoon(sf::Vector2f _pos, sf::Vector2f _vel = { 0,0 });

	void init() override;
};

