#pragma once
#include "Includes.h"
#include"Inventory.h"

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void render(const std::unique_ptr<sf::RenderWindow>& window) = 0;
	virtual void RenderUI(const std::unique_ptr<sf::RenderWindow>& _window) = 0;
	virtual void interact() = 0;
	virtual void update() = 0;

	void setPosition(sf::Vector2f _pos) { sprite.setPosition(_pos); };
	void setNodeId(int _id) { currentNodeId = _id; }
	int getID() const { return currentNodeId; }
	const std::unique_ptr<Inventory>& getInventory() const { return inventory; }
	std::unique_ptr<RenderableInventory>& GetRenderableInventory() { return renderableInventory; }
	virtual sf::Vector2f GetPosition() const = 0;

protected:
	sf::Sprite sprite;
	std::unique_ptr<Inventory> inventory;
	int currentNodeId;
	std::unique_ptr<RenderableInventory> renderableInventory;
};

