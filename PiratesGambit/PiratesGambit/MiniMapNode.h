#pragma once
#include "Includes.h"
#include "Structs.h"
#include "Node.h"
class MiniMapNode
{
public:
	MiniMapNode(sf::Vector2f _pos, int _size);

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void updateColor(const std::shared_ptr<Node>& _node);
	void updatePlayerLocation();
private:
	sf::RectangleShape node;
};

