#include "CannonBuilding.h"

CannonBuilding::CannonBuilding(const std::shared_ptr<Player>& _playerRef)
{
	buildingSprite.setTexture(TextureManager::getInstance().getTexture("BUILDINGS"));

	sf::IntRect buildingBounds = { 96, 0, 48, 48 };

	buildingSprite.setTextureRect(buildingBounds);
	buildingSprite.setOrigin(24, 24);
	buildingSprite.setScale(2, 2);

	maxUnitAmount = 3;
	unitType = CANNON;
	costPerTroop = 500;

	popUp = std::make_unique<BuildingPopUp>();

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(80, 80));

}
