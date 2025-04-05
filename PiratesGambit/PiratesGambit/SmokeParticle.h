#pragma once
#include "Particle.h"
class SmokeParticle :
    public Particle
{
public:
    SmokeParticle(sf::Vector2f _pos);
    void Update(float _dt) override;
private:
    float riseSpeed;
    float swayAmount;
    float rotationSpeed;
    float lifetime;
    float timeAlive;
};

