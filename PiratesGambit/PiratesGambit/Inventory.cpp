#include "Inventory.h"

#include "Mouse.h"

bool Inventory::inventoryOpen = false;

Inventory::Inventory()
{
	renderableInventory = new RenderableInventory(2,4);
}

void Inventory::addItem(std::unique_ptr<InventoryItem> _item)
{
	inventory.push_back(std::move(_item));
}

std::unique_ptr<InventoryItem> Inventory::removeItem(std::string _name)
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

void Inventory::checkMousePosition()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for(auto& slot : renderableInventory->getSlots())
	{
		if(Mouse::getInstance().getHasClicked() && slot->getIsOccupied())
		{
			if (slot->getBackgroundSprite().getGlobalBounds().contains(mousePos))
			{
				std::unique_ptr<InventoryItem> item = removeItem(slot->getOccupiedBy());
			}
		}
	}
}
