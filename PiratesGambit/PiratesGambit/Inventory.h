#pragma once
#include "Includes.h"
#include"InventoryItem.h"
#include "RenderableIventory.h"

class Inventory
{
public:
	Inventory();

	void addItem(std::unique_ptr<InventoryItem> _item);
	std::unique_ptr<InventoryItem> removeItem(std::string _name);

	void openInventory();
	void closeInventory();

	bool combineItems(const std::unique_ptr<InventoryItem>& _item);

	void update();
	void checkMousePosition();

	const std::vector<std::unique_ptr<InventoryItem>>& getItems() const { return inventory; }
	RenderableInventory* getRenderableInventory() const { return renderableInventory; }

	static bool isInventoryOpen() { return inventoryOpen; }

private:
	std::vector<std::unique_ptr<InventoryItem>> inventory;
	RenderableInventory* renderableInventory;

	static bool inventoryOpen;
};

