#pragma once
#include"MiniMapNode.h"
class MiniMap
{
public:
	MiniMap(sf::Vector2f _pos, int _mapSize, int _nodeSize);
	~MiniMap() = default;
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void updateColor(int _index, const std::shared_ptr<Node>& _node);
	void updatePlayerLocation(int _index);
private:
	std::vector<std::unique_ptr<MiniMapNode>> miniMapNodes;
	sf::RectangleShape background;
	int nodeSize = 4;
};

