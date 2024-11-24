#pragma once
#include"InventoryItem.h"
#include "TextureManager.h"

class CannonBallItem : public InventoryItem
{
public:
	CannonBallItem(int _stackCount)
	{
		itemSprite.setTexture(TextureManager::getInstance().getTexture("CANNON_BALL_ICON"));
		itemSprite.setScale(2, 2);
		currentStack = _stackCount;
		itemName = "CannonBall";
	}
private:
};

