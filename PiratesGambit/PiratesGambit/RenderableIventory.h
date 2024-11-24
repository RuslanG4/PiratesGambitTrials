#pragma once
#include"Includes.h"
#include "InventoryItem.h"
#include"InventorySlot.h"

class RenderableInventory
{
public:
	RenderableInventory(int _rows, int _cols);

	void setUpInventory(int _rows, int _cols);
	void passItems(std::vector<std::unique_ptr<InventoryItem>>& _currentItems);
	void render(sf::RenderWindow& _win);

	std::vector<InventorySlot*> getSlots() const { return inventorySlots; }

private:
	sf::RectangleShape inventoryBackground;
	std::vector<InventorySlot*> inventorySlots;
};

