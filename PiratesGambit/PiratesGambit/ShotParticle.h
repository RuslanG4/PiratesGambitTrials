#pragma once
#include "Particle.h"

/// <summary>
/// Particle for smoke out of gun effect
/// </summary>
class ShotParticle : public Particle
{
public:
	/// <summary>
	/// Constructor for textures
	/// </summary>
	/// <param name="_pos"></param>
	ShotParticle(sf::Vector2f _pos);

	void Update(float _dt) override;

private:
};

