#pragma once
#include "InventoryItem.h"
#include "TextureManager.h"

class Coins : public InventoryItem
{
public:
	Coins(int _stackCount)
	{
		itemSprite.setTexture(TextureManager::getInstance().getTexture("COIN_ICON"));
		itemSprite.setScale(2, 2);
		currentStack = _stackCount;
		itemName = "Coins";
	}
private:
};

