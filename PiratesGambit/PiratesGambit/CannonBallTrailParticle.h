#pragma once
#include "Particle.h"
class CannonBallTrailParticle :
    public Particle
{
public:
    CannonBallTrailParticle(sf::Vector2f _pos, sf::Vector2f _vel);
    void Update(float _dt) override;
private:
    sf::Vector2f vel;
    float lifetime;
    float timeAlive;
};

