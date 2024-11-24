#include "InventorySlot.h"

#include "TextureManager.h"

InventorySlot::InventorySlot(int _x, int _y, int _id)
{
	slotSprite.setPosition(sf::Vector2f(_x, _y));
	slotSprite.setSize(sf::Vector2f(64,64));
	slotSprite.setFillColor(sf::Color::Transparent);
	slotSprite.setOutlineColor(sf::Color::Black);
	slotSprite.setOutlineThickness(3.f);

	midPoint = sf::Vector2f(_x, _y);

	stackSize.setFont(TextureManager::getInstance().getFont());
	stackSize.setCharacterSize(16);
	stackSize.setString("1");
}

void InventorySlot::configureSprite(int _stackSize)
{
	ItemSprite.setPosition(midPoint);

	stackSize.setString(std::to_string(_stackSize));
	stackSize.setPosition(midPoint.x + 48, midPoint.y+48);
}

void InventorySlot::clearSlot()
{
	stackSize.setString("0");
	sf::Sprite emptySprite;
	setSprite(emptySprite);

	isOccupied = false;
	occupiedBy = "";
}
