#pragma once
#include"Includes.h"

class InventoryItem
{
public:
	sf::Sprite getSprite() const { return itemSprite; }
protected:
	sf::Sprite itemSprite;
};

