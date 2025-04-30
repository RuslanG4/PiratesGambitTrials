#include "BoatTrailParticle.h"

BoatTrailParticle::BoatTrailParticle(sf::Vector2f _pos, sf::Vector2f _vel)
{
    particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("BOAT_TRAIL_PARTICLE"));
    particleSpriteSheet.setPosition(_pos + _vel * 2.f);
    particleSpriteSheet.setOrigin(16, 16);

    lifetime = 0.5f + static_cast<float>(rand() % 100) / 100.0f;

    timeAlive = 0.0f;

    float randomRotation = static_cast<float>(rand() % 360);
    particleSpriteSheet.setRotation(randomRotation);
}

void BoatTrailParticle::Update(float _dt)
{
    timeAlive += _dt * 0.001f;
    if (timeAlive > lifetime)
        animationFinish = true;

    particleSpriteSheet.setPosition(particleSpriteSheet.getPosition() + vel);

    float progress = timeAlive / lifetime;

    float alpha = 255 * (1.0f - (timeAlive / lifetime));
    particleSpriteSheet.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

    float scale = 2.5f - progress;
    scale = std::max(scale, 0.0f);
    particleSpriteSheet.setScale(scale, scale);
}
