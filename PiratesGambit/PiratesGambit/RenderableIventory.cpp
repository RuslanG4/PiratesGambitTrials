#include "RenderableIventory.h"

#include "TextureManager.h"

RenderableInventory::RenderableInventory(int _rows, int _cols)
{
	setUpInventory(_rows, _cols);
}

void RenderableInventory::setUpInventory(int _rows, int _cols)
{
	const float padding = 15;

	inventoryBackground.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	inventoryBackground.setSize(sf::Vector2f(64 * _rows + (padding * 3), 64 * _cols + (padding * 5)));
	sf::Vector2f size = inventoryBackground.getSize();
	inventoryBackground.setOrigin(sf::Vector2f(size.x/2, size.y/2));
	inventoryBackground.setFillColor(sf::Color::Red);

	sf::Vector2f topLeftOfBG = sf::Vector2f(
		inventoryBackground.getPosition().x - inventoryBackground.getOrigin().x + padding,
		inventoryBackground.getPosition().y - inventoryBackground.getOrigin().y + padding
	);

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			float posX = topLeftOfBG.x + x * (64 + padding); //64 is size of slot
			float posY = topLeftOfBG.y + y * (64 + padding);

			inventorySlots.push_back(new InventorySlot(posX, posY, x + y * 4));
		}
	}
	
}

void RenderableInventory::passItems(std::vector<std::unique_ptr<InventoryItem>>& _currentItems)
{
	for(int i =0;i< _currentItems.size(); i++)
	{
		inventorySlots[i]->updateSlot(true);
		inventorySlots[i]->setOccupiedBy(_currentItems[i]->getItemName());
		inventorySlots[i]->setSprite(_currentItems[i]->getSprite());
		inventorySlots[i]->configureSprite(_currentItems[i]->getStackSize());
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
		_win.draw(slot->getTest());
	}
	
}

