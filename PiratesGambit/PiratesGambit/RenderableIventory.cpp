#include "RenderableIventory.h"

#include "TextureManager.h"

void RenderableInventory::Init()
{
	constexpr float padding = 50;

	inventoryBackground.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	inventoryBackground.setSize(sf::Vector2f(96 * _cols + (padding * 3), 96 * _rows + (padding * 5)));
	sf::Vector2f size = inventoryBackground.getSize();
	inventoryBackground.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	inventoryBackground.setFillColor(sf::Color(0, 0, 0, 180));

	sf::Vector2f topLeftOfBG = sf::Vector2f(
		inventoryBackground.getPosition().x - inventoryBackground.getOrigin().x + padding,
		inventoryBackground.getPosition().y - inventoryBackground.getOrigin().y + padding
	);

	for (int y = 0; y < _rows; y++)
	{
		for (int x = 0; x < _cols; x++)
		{
			float posX = topLeftOfBG.x + x * (96 + padding);
			float posY = topLeftOfBG.y + y * (96 + padding);

			inventorySlots.push_back(new InventorySlot(posX, posY, x + y * 4));
		}
	}
}

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
	if (isMenuOpen) {
		window->setView(window->getDefaultView());
		window->draw(inventoryBackground);
		for (auto& slot : inventorySlots)
		{
			window->draw(slot->getBackgroundSprite());
			window->draw(slot->getItemSprite());
			window->draw(slot->getTest());
		}
	}
}

