#include "Inventory.h"

Inventory::Inventory()
{
	renderableInventory = new RenderableInventory();
}

void Inventory::addItem(std::unique_ptr<InventoryItem> _item)
{
	inventory.push_back(std::move(_item));
}

void Inventory::takeAwayItem(InventoryItem _item)
{
}

void Inventory::openInventory()
{
	inventoryOpen = true;
	renderableInventory->passItems(inventory);
}

void Inventory::closeInventory()
{
	inventoryOpen = false;
}

void Inventory::update()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) && inventoryOpen)
	{
		closeInventory();
	}
}
