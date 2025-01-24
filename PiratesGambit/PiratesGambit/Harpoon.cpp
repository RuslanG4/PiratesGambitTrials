#include "Harpoon.h"

Harpoon::Harpoon(sf::Vector2f _pos, sf::Vector2f _vel)
{
	position = _pos;
	velocity = _vel;
}

void Harpoon::init()
{
	body.setTexture(TextureManager::getInstance().getTexture("HARPOON"));
	body.setOrigin(8, 8);
	body.setScale(2.5, 2.5);
	body.setPosition(position);

	float angleRadians = std::atan2(velocity.y, velocity.x);

	float angleDegrees = angleRadians * 180.f / static_cast<float>(Utility::PI);

	
	body.setRotation(angleDegrees);
}
