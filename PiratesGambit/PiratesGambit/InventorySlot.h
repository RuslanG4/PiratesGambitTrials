#pragma once
#include"Includes.h"

class InventorySlot
{
public:
	InventorySlot(int _x, int _y, int _id);

	sf::RectangleShape getBackgroundSprite() const { return slotSprite; }
	sf::Sprite getItemSprite() const { return ItemSprite; }
	void setSprite(sf::Sprite _sprite) { ItemSprite = _sprite; }
	void configureSprite();
private:
	sf::RectangleShape slotSprite;
	sf::Sprite ItemSprite;
	int m_id;

	sf::Vector2f midPoint;

};

