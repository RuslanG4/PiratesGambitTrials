#include "RenderableIventory.h"

RenderableInventory::RenderableInventory()
{
	setUpInventory();
}

void RenderableInventory::setUpInventory()
{
	inventoryBackground.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	inventoryBackground.setSize(sf::Vector2f(256, 384));
	inventoryBackground.setOrigin(sf::Vector2f(128, 192));
	inventoryBackground.setFillColor(sf::Color::Red);

	sf::Vector2f topLeftOfBG = sf::Vector2f(inventoryBackground.getPosition().x - 128 + 64, inventoryBackground.getPosition().y - 192 + 64);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			inventorySlots.push_back(new InventorySlot(topLeftOfBG.x + (x * 64), topLeftOfBG.y + ( y * 64), x + y * 4));
		}
	}
	
}

void RenderableInventory::passItems(std::vector<std::unique_ptr<InventoryItem>>& _currentItems)
{
	for(int i =0;i< _currentItems.size(); i++)
	{
		inventorySlots[i]->setSprite(_currentItems[i]->getSprite());
		inventorySlots[i]->configureSprite();
	}
}

void RenderableInventory::render(sf::RenderWindow& _win)
{
	_win.setView(_win.getDefaultView());
	_win.draw(inventoryBackground);
	for(auto& slot: inventorySlots)
	{
		_win.draw(slot->getBackgroundSprite());
		_win.draw(slot->getItemSprite());
	}
}

