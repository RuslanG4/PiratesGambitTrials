#include "RenderableIventory.h"

#include "TextureManager.h"

void RenderableInventory::passItems(const std::vector<std::unique_ptr<InventoryItem>>& _currentItems)
{
	for(auto& slot : inventorySlots)
	{
		slot->clearSlot();
	}
	for(int i =0; i < _currentItems.size(); i++)
	{
		inventorySlots[i]->updateSlot(true);
		inventorySlots[i]->setOccupiedBy(_currentItems[i]->getItemName());
		inventorySlots[i]->setSprite(_currentItems[i]->getSprite());
		inventorySlots[i]->configureSprite(_currentItems[i]->getStackSize());
	}
}

void RenderableInventory::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->setView(window->getDefaultView());
	window->draw(inventoryBackground);
	for(auto& slot: inventorySlots)
	{
		window->draw(slot->getBackgroundSprite());
		window->draw(slot->getItemSprite());
		window->draw(slot->getTest());
	}
}

