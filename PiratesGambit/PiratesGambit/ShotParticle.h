#pragma once
#include "Particle.h"

class ShotParticle : public Particle
{
public:
	ShotParticle(sf::Vector2f _pos);

	void Update(float _dt) override;

private:
};

