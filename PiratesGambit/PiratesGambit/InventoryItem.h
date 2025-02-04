#pragma once
#include"Includes.h"

class InventoryItem
{
public:
	InventoryItem() = default;

	void addToCurrentStack(int _amount) { currentStack += _amount; }

	void removeFromCurrentStack(int _amount) { currentStack -= _amount; }

	sf::Sprite getSprite() const { return itemSprite; }
	int getStackSize() const { return currentStack; }
	std::string getItemName() const { return itemName; }
protected:
	sf::Sprite itemSprite;
	int currentStack;
	std::string itemName;
};

