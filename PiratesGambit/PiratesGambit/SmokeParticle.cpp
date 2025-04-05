#include "SmokeParticle.h"

SmokeParticle::SmokeParticle(sf::Vector2f _pos)
{
    particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("SMOKE_PARTICLE"));
    particleSpriteSheet.setPosition(_pos);
	particleSpriteSheet.setOrigin(16, 16);
    

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> Scale(0.5f, 1.5f);

	float scale = Scale(gen);

    particleSpriteSheet.setScale(scale, scale);

    std::uniform_real_distribution<float> riseSpeedDist(0.01f, 0.03f); 
    std::uniform_real_distribution<float> swayDist(0.1f, 0.3f);   
    std::uniform_real_distribution<float> rotationDist(-0.05f, 0.05f); 

    riseSpeed = riseSpeedDist(gen);         
    swayAmount = swayDist(gen);
    rotationSpeed = rotationDist(gen);
    lifetime = 0.8f + static_cast<float>(rand() % 100) / 100.0f; // longer life

    timeAlive = 0.0f;
}

void SmokeParticle::Update(float _dt)
{
    timeAlive += _dt * 0.001f;
    if (timeAlive > lifetime)
        animationFinish = true;

    float sway = std::sin(timeAlive * 6.0f) * swayAmount; // faster sway
    particleSpriteSheet.move(sway, -riseSpeed * _dt);     // negative = upwards
    particleSpriteSheet.rotate(rotationSpeed * _dt);

    // Fade out
    float alpha = 255 * (1.0f - (timeAlive / lifetime));
    particleSpriteSheet.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}
