#include "GunnerBuilding.h"

GunnerBuilding::GunnerBuilding(const std::shared_ptr<Player>& _playerRef)
{
	buildingSprite.setTexture(TextureManager::getInstance().getTexture("BUILDINGS"));

	sf::IntRect buildingBounds = { 48, 0, 48, 48 };

	buildingSprite.setTextureRect(buildingBounds);
	buildingSprite.setOrigin(24, 24); //half of 48
	buildingSprite.setScale(2, 2);

	maxUnitAmount = 7;
	unitType = GUNNER;

	popUp = std::make_unique<BuildingPopUp>();

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(80, 80));

}
