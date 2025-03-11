#include "EnemyBoat.h"

void EnemyBoat::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(boatSprite);
}

void EnemyBoat::update(double dt)
{
}

void EnemyBoat::RotateTowardsPlayer(sf::Vector2f _pos)
{
    if (_pos.x != 0 || _pos.y != 0)
    {
        float targetAngle = std::atan2(_pos.y, _pos.x) * 180 / Utility::PI;

        targetAngle -= 90;

        float currentAngle = boatSprite.getRotation();

        float angleDiff = targetAngle - currentAngle;
        if (angleDiff > 180) angleDiff -= 360;
        if (angleDiff < -180) angleDiff += 360;

        float rotationSpeed = 0.075f; 
        float newAngle = currentAngle + angleDiff * rotationSpeed;

        boatSprite.setRotation(newAngle);
    }
}
