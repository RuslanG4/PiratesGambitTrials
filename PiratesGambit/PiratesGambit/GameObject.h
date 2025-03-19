#pragma once
#include "HitBox.h"
#include "Includes.h"
#include"Inventory.h"

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void render(const std::unique_ptr<sf::RenderWindow>& window) = 0;
	virtual void interact() = 0;
	virtual void update(float _dt) = 0;

	void setPosition(sf::Vector2f _pos) { sprite.setPosition(_pos); myHitbox->setPosition(_pos); }
	void setNodeId(int _id) { currentNodeId = _id; }
	int getID() const { return currentNodeId; }
	const std::unique_ptr<Inventory>& getInventory() const { return inventory; }
	virtual sf::Vector2f GetPosition() const = 0;

	sf::FloatRect GetHitBox()const { return myHitbox->GetGlobalBounds(); }

protected:
	sf::Sprite sprite;
	int currentNodeId;

	std::unique_ptr<Inventory> inventory;
	std::unique_ptr<HitBox> myHitbox;
};

