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

	const std::vector<std::unique_ptr<InventoryItem>>& getItems() const { return inventory; }
	static bool isInventoryOpen() { return inventoryOpen; }

private:
	std::vector<std::unique_ptr<InventoryItem>> inventory;

	static bool inventoryOpen;
};

