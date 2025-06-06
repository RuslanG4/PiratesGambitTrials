#pragma once
#include "Includes.h"
#include"InventoryItem.h"
#include "RenderableIventory.h"

class Inventory
{
public:
	Inventory();

	void addItem(std::unique_ptr<InventoryItem> _item);
	std::unique_ptr<InventoryItem> removeItem(ItemName _name);
	bool removeItemFromStack(ItemName _name);

	const InventoryItem* getItem(ItemName _name);

	void openInventory();
	void closeInventory();

	bool combineItems(const std::unique_ptr<InventoryItem>& _item);

	void update();

	const std::vector<std::unique_ptr<InventoryItem>>& getItems() const { return inventory; }
	static bool isInventoryOpen() { return inventoryOpen; }

	bool IsPersonalOpen() const { return personalOpen; }

private:
	std::vector<std::unique_ptr<InventoryItem>> inventory;

	bool personalOpen{ false };
	static bool inventoryOpen;
};

