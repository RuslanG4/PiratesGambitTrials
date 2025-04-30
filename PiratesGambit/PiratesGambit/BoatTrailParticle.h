#pragma once
#include "Particle.h"
class BoatTrailParticle :
    public Particle
{
public:
    BoatTrailParticle(sf::Vector2f _pos, sf::Vector2f _vel);
    void Update(float _dt) override;
private:
    sf::Vector2f vel;
    float lifetime;
    float timeAlive;
};

