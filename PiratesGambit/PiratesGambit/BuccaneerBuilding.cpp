#include "BuccaneerBuilding.h"

BuccaneerBuilding::BuccaneerBuilding(const std::shared_ptr<Player>& _playerRef)
{
	buildingSprite.setTexture(TextureManager::getInstance().getTexture("BUILDINGS"));

	sf::IntRect buildingBounds = { 0, 0, 48, 48 };

	buildingSprite.setTextureRect(buildingBounds);
	buildingSprite.setOrigin(24, 24); //half of 48
	buildingSprite.setScale(2, 2);

	maxUnitAmount = 14;
	unitType = BUCCANEER;

	popUp = std::make_unique<BuildingPopUp>();

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(58, 58));
}
