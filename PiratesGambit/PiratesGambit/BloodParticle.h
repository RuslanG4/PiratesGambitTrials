#pragma once
#include "Particle.h"

class BloodParticle : public Particle
{
public:
	BloodParticle(sf::Vector2f _pos);

	void Update(float _dt) override;

private:
};

