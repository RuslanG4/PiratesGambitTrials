#pragma once
#include"Includes.h"
#include "Enums.h"

class InventorySlot
{
public:
	InventorySlot(int _x, int _y, int _id);

	sf::RectangleShape getBackgroundSprite() const { return slotSprite; }
	sf::Sprite getItemSprite() const { return ItemSprite; }
	sf::Text getTest() const { return stackSize; }
	void setSprite(const sf::Sprite& _sprite) { ItemSprite = _sprite; }
	void configureSprite(int _stackSize);
	void setOccupiedBy(ItemName _who) { occupiedBy = _who; }
	ItemName getOccupiedBy() const { return occupiedBy; }

	void updateSlot(bool _status) { isOccupied = _status; }
	void clearSlot();
	bool getIsOccupied() const { return isOccupied; }
private:
	sf::RectangleShape slotSprite;
	sf::Sprite ItemSprite;
	int m_id;

	ItemName occupiedBy;
	bool isOccupied{ false };

	sf::Vector2f midPoint;

	sf::Text stackSize;

};

