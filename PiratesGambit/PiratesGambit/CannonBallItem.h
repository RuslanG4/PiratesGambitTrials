#pragma once
#include"InventoryItem.h"
#include "TextureManager.h"

class CannonBallItem : public InventoryItem
{
public:
	CannonBallItem()
	{
		itemSprite.setTexture(TextureManager::getInstance().getTexture("CANNON_BALL"));
	};
private:
};

