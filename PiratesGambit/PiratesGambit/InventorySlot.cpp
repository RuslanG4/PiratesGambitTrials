#include "InventorySlot.h"

#include "TextureManager.h"

InventorySlot::InventorySlot(int _x, int _y, int _id)
{
	slotSprite.setPosition(sf::Vector2f(_x, _y));
	slotSprite.setSize(sf::Vector2f(96,96));
	slotSprite.setFillColor(sf::Color(130,130,130,180));
	slotSprite.setOutlineColor(sf::Color::Black);
	slotSprite.setOutlineThickness(3.f);

	midPoint = sf::Vector2f(_x, _y);

	stackSize.setFont(TextureManager::getInstance().getFont());
	stackSize.setCharacterSize(16);
	stackSize.setString("1");
}

void InventorySlot::configureSprite(int _stackSize)
{
	ItemSprite.setPosition(slotSprite.getPosition());

	stackSize.setString(std::to_string(_stackSize));
	stackSize.setPosition(slotSprite.getPosition().x + 48, slotSprite.getPosition().y+48);
}

void InventorySlot::clearSlot()
{
	stackSize.setString("0");
	stackSize.setPosition(sf::Vector2f(-1000, 10000));
	sf::Sprite emptySprite;
	setSprite(emptySprite);

	isOccupied = false;
	occupiedBy = NO_ITEM;
}
