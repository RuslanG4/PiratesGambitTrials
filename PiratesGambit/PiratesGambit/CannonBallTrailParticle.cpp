#include "CannonBallTrailParticle.h"

CannonBallTrailParticle::CannonBallTrailParticle(sf::Vector2f _pos, sf::Vector2f _vel)
{
    particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("SMOKE_PARTICLE"));
    particleSpriteSheet.setPosition(_pos + _vel * 2.f);
    particleSpriteSheet.setOrigin(16, 16);


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> Scale(0.2f, 0.6f);

    float scale = Scale(gen);

    particleSpriteSheet.setScale(scale, scale);

    lifetime = 0.5f + static_cast<float>(rand() % 100) / 100.0f;

    timeAlive = 0.0f;
}

void CannonBallTrailParticle::Update(float _dt)
{
    timeAlive += _dt * 0.001f;
    if (timeAlive > lifetime)
        animationFinish = true;
    
    particleSpriteSheet.setPosition(particleSpriteSheet.getPosition() + vel);

    // Fade out
    float alpha = 255 * (1.0f - (timeAlive / lifetime));
    particleSpriteSheet.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}
