#include "BuccaneerBuilding.h"

BuccaneerBuilding::BuccaneerBuilding()
{
	buildingSprite.setTexture(TextureManager::getInstance().getTexture("BUILDINGS"));

	sf::IntRect buildingBounds = { 0, 0, 48, 48 };

	buildingSprite.setTextureRect(buildingBounds);
	buildingSprite.setOrigin(24, 24); //half of 48
	buildingSprite.setScale(2, 2);

	buildingUI = std::make_unique<HireRecruitUI>();
}
