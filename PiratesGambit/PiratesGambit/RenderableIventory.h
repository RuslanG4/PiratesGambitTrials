#pragma once
#include"Includes.h"
#include "InventoryItem.h"
#include"InventorySlot.h"

class RenderableInventory
{
public:
	RenderableInventory();

	void setUpInventory();
	void passItems(std::vector<std::unique_ptr<InventoryItem>>& _currentItems);
	void render(sf::RenderWindow& _win);

private:
	sf::RectangleShape inventoryBackground;
	std::vector<InventorySlot*> inventorySlots;
};

