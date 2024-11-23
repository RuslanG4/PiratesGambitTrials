#include "InventorySlot.h"

InventorySlot::InventorySlot(int _x, int _y, int _id)
{
	slotSprite.setPosition(sf::Vector2f(_x, _y));
	slotSprite.setSize(sf::Vector2f(64,64));
	slotSprite.setFillColor(sf::Color::Transparent);
	slotSprite.setOutlineColor(sf::Color::Black);
	slotSprite.setOutlineThickness(3.f);

	midPoint = sf::Vector2f(_x + 32, _y + 32);
}

void InventorySlot::configureSprite()
{
	ItemSprite.setOrigin(ItemSprite.getGlobalBounds().getSize().x / 2, ItemSprite.getGlobalBounds().getSize().y / 2);
	ItemSprite.setPosition(midPoint);
}
