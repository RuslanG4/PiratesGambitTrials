#include "MiniMap.h"

MiniMap::MiniMap(sf::Vector2f _pos, int _mapSize, int _nodeSize)
{
	int rows = CHUNK_NODE_ROWS * _mapSize;  //identifies the amount of rows
	int cols = CHUNK_NODE_COLS * _mapSize;  //identifies the amount of columns

	nodeSize = _nodeSize; // set node size

	miniMapNodes.reserve(rows * cols); // reserve memory

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			sf::Vector2f pos = sf::Vector2f(_pos.x + x * nodeSize, _pos.y + y * nodeSize);
			miniMapNodes.push_back(std::make_unique<MiniMapNode>(pos, nodeSize));
		}
	}

	background.setSize(sf::Vector2f(rows * nodeSize, cols * nodeSize) + sf::Vector2f(nodeSize * 2, nodeSize * 2)); // padding
	background.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black
	background.setPosition(_pos.x - nodeSize, _pos.y - nodeSize); // adjust position for padding
}

void MiniMap::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->setView(window->getDefaultView());
	window->draw(background); 
	for (const auto& node : miniMapNodes)
	{
		node->render(window);
	}
}

void MiniMap::updateColor(int _index, const std::shared_ptr<Node>& _node)
{
	if (_index >= 0 && _index < miniMapNodes.size())
	{
		miniMapNodes[_index]->updateColor(_node);
	}
}

void MiniMap::updatePlayerLocation(int _index)
{
	if (_index >= 0 && _index < miniMapNodes.size())
	{
		miniMapNodes[_index]->updatePlayerLocation();
	}
}
