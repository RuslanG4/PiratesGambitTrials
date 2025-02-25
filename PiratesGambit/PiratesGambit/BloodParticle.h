#pragma once
#include "Particle.h"


/// <summary>
/// Particle for when Units take damage
/// </summary>
class BloodParticle : public Particle
{
public:
	/// <summary>
	/// Constructor for textures
	/// </summary>
	/// <param name="_pos"></param>
	BloodParticle(sf::Vector2f _pos);

	void Update(float _dt) override;

private:
};

