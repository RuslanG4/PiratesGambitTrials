#pragma once
#include "Particle.h"
class LeafParticle :
    public Particle
{
public:
    LeafParticle(sf::Vector2f _pos);
	void Update(float _dt) override;
private:
    float fallSpeed;
    float swayAmount;
    float rotationSpeed;
    float lifetime;
    float timeAlive;
};

