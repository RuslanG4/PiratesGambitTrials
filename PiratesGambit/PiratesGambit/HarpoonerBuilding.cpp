#include "HarpoonerBuilding.h"

HarpoonerBuilding::HarpoonerBuilding(const std::shared_ptr<Player>& _playerRef)
{
	buildingSprite.setTexture(TextureManager::getInstance().getTexture("BUILDINGS"));

	sf::IntRect buildingBounds = { 0, 48, 48, 48 };

	buildingSprite.setTextureRect(buildingBounds);
	buildingSprite.setOrigin(24, 24);
	buildingSprite.setScale(2, 2);

	maxUnitAmount = 5;
	unitType = HARPOONER;
	costPerTroop = 250;

	popUp = std::make_unique<BuildingPopUp>();

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(80, 80));
}
