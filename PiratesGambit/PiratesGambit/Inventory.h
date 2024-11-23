#pragma once
#include "Includes.h"
#include"InventoryItem.h"
#include "RenderableIventory.h"
class Inventory
{
public:
	Inventory();

	void addItem(std::unique_ptr<InventoryItem> _item);
	void takeAwayItem(InventoryItem _item);

	void openInventory();
	void closeInventory();

	void update();

	//std::vector<std::unique_ptr<InventoryItem>> getItems() const { return inventory; }
	RenderableInventory* getRenderableInventory() const { return renderableInventory; }

	bool isInventoryOpen() const { return inventoryOpen; }

private:
	std::vector<std::unique_ptr<InventoryItem>> inventory;
	RenderableInventory* renderableInventory;

	bool inventoryOpen{false};
};

