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

	stackSize.setFont(TextureManager::getInstance().getFont("Varsity"));
	stackSize.setCharacterSize(20);
	stackSize.setString("1");
}

void InventorySlot::configureSprite(int _stackSize)
{
	ItemSprite.setPosition(slotSprite.getPosition() + sf::Vector2f(8,8));
	ItemSprite.setScale(2.5f, 2.5f);

	stackSize.setString(std::to_string(_stackSize));
	stackSize.setPosition(ItemSprite.getPosition().x + ItemSprite.getGlobalBounds().width - 28, ItemSprite.getPosition().y + +ItemSprite.getGlobalBounds().height - 16);
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
