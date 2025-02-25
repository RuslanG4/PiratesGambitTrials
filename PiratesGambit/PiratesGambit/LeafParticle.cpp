#include "LeafParticle.h"

LeafParticle::LeafParticle(sf::Vector2f _pos)
{
    particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("LEAF_PARTICLE"));
    particleSpriteSheet.setPosition(_pos);
    particleSpriteSheet.setScale(0.5f, 0.5f); // Adjust for small leaves

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(0.01f, 0.03f);
    std::uniform_real_distribution<float> swayDist(0.1f, 0.5f);
    std::uniform_real_distribution<float> rotationDist(-0.01f, 0.06f);

    fallSpeed = speedDist(gen);
    swayAmount = swayDist(gen);
    rotationSpeed = rotationDist(gen);
    lifetime = 0.4f + static_cast<float>(rand() % 100) / 50.0f; // Random lifespan

    timeAlive = 0.0f;
}

void LeafParticle::Update(float _dt)
{
    timeAlive += _dt * 0.001;
    if (timeAlive > lifetime)
        animationFinish = true; // Leaf should disappear

    float sway = std::sin(timeAlive) * swayAmount;
    particleSpriteSheet.move(sway, fallSpeed * _dt);
    particleSpriteSheet.rotate(rotationSpeed * _dt);

    // Fade out effect
    float alpha = 255 * (1.0f - (timeAlive / lifetime));
    particleSpriteSheet.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

}
