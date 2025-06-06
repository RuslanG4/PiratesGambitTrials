#include "Inventory.h"

#include "Mouse.h"

bool Inventory::inventoryOpen = false;

Inventory::Inventory()
{
	
}

void Inventory::addItem(std::unique_ptr<InventoryItem> _item)
{
	combineItems(_item);
	inventory.push_back(std::move(_item));
}

std::unique_ptr<InventoryItem> Inventory::removeItem(ItemName _name)
{
	auto it = std::find_if(inventory.begin(), inventory.end(), [&](const std::unique_ptr<InventoryItem>& item) {
		return item->getItemName() == _name;
		});

	if (it != inventory.end()) {
		std::unique_ptr<InventoryItem> removedItem = std::move(*it);
		inventory.erase(it);
		return removedItem;
	}
	return nullptr;
}

bool Inventory::removeItemFromStack(ItemName _name)
{
	auto it = std::find_if(inventory.begin(), inventory.end(), [&](const std::unique_ptr<InventoryItem>& item) {
		return item->getItemName() == _name;
		});

	if (it != inventory.end()) {
		(*it)->removeFromCurrentStack(1);
		if ((*it)->getStackSize() <= 0) {
			removeItem(_name);
		}
		return true;
	}
	return false;
}

const InventoryItem* Inventory::getItem(ItemName _name)  
{  
   auto it = std::find_if(inventory.begin(), inventory.end(), [&](const std::unique_ptr<InventoryItem>& item) {  
       return item->getItemName() == _name;  
   });  

   if (it != inventory.end()) {  
       return it->get();  
   }  
   return nullptr;  
}

void Inventory::openInventory()
{
	inventoryOpen = true;
	personalOpen = true;
	RenderableInventory::getInstance().OpenMenu();
}

void Inventory::closeInventory()
{
	inventoryOpen = false;
	personalOpen = false;
	RenderableInventory::getInstance().CloseMenu();
}

bool Inventory::combineItems(const std::unique_ptr<InventoryItem>& _item)
{
	auto it = std::find_if(inventory.begin(), inventory.end(), [&](const std::unique_ptr<InventoryItem>& item) {
		return item->getItemName() == _item->getItemName();
		});

	if (it != inventory.end()) {
		
		std::unique_ptr<InventoryItem> removedItem = std::move(*it);
		_item->addToCurrentStack(removedItem->getStackSize());
		inventory.erase(it);
		return true;
	}

	return false;
}

void Inventory::update()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) && IsPersonalOpen())
	{
		closeInventory();
	}
}


