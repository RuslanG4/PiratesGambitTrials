#pragma once
#include "Particle.h"
/// <summary>
/// Particle for explosion effect
/// </summary>
class ExplosionParticle : public Particle
{
public:
	/// <summary>
	/// Constructor for textures
	/// </summary>
	/// <param name="_pos"></param>
	ExplosionParticle(sf::Vector2f _pos);

	void Update(float _dt) override;

private:
};
