#pragma once
#include"Includes.h"
#include "InventoryItem.h"
#include"InventorySlot.h"

class RenderableInventory
{
public:
	void passItems(const std::vector<std::unique_ptr<InventoryItem>>& _currentItems);
	void render(const std::unique_ptr<sf::RenderWindow>& window);

	std::vector<InventorySlot*> getSlots() const { return inventorySlots; }

protected:
	sf::RectangleShape inventoryBackground;
	std::vector<InventorySlot*> inventorySlots;
};

