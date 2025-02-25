#include "BarrelInventory.h"

BarrelInventory::BarrelInventory(int _rows, int _cols)
{
	constexpr float padding = 50;

	inventoryBackground.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	inventoryBackground.setSize(sf::Vector2f(96 * _cols + (padding * 3), 96 * _rows + (padding * 5)));
	sf::Vector2f size = inventoryBackground.getSize();
	inventoryBackground.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	inventoryBackground.setFillColor(sf::Color(0,0,0,180));

	sf::Vector2f topLeftOfBG = sf::Vector2f(
		inventoryBackground.getPosition().x - inventoryBackground.getOrigin().x + padding,
		inventoryBackground.getPosition().y - inventoryBackground.getOrigin().y + padding
	);

	for (int y = 0; y < _rows; y++)
	{
		for (int x = 0; x < _cols; x++)
		{
			float posX = topLeftOfBG.x + x * (96 + padding); //64 is size of slot
			float posY = topLeftOfBG.y + y * (96 + padding);

			inventorySlots.push_back(new InventorySlot(posX, posY, x + y * 4));
		}
	}
}
