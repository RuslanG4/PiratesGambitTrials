#pragma once
#include "Includes.h"
#include"Inventory.h"

class GameObject
{
public:
	virtual void render(sf::RenderWindow& _win) = 0;
	virtual void interact() = 0;
	virtual void update() = 0;

	void setPosition(sf::Vector2f _pos) { sprite.setPosition(_pos); };
	void setNodeId(int _id) { currentNodeId = _id; }
	int getID() const { return currentNodeId; }
	const std::unique_ptr<Inventory>& getInventory() const { return inventory; }
protected:
	sf::Sprite sprite;
	std::unique_ptr<Inventory> inventory;
	int currentNodeId;
};

