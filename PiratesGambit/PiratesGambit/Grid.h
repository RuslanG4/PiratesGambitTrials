#pragma once
#include"Includes.h"
#include"Node.h"

class Grid
{
public:
	Grid(int density,sf::Font& _font);
	void drawGrid(sf::RenderWindow& _window);
	void addNeighbours(int _currentNodeId);
	int const getNodeSize() const { return gridNodeSize; };

	void WaveFunctionCollapse(int _startNode, sf::RenderWindow& window);

	void wait();

	void ApplyCelular(int _interations, sf::RenderWindow& window);
	void FindLand(sf::RenderWindow& m_window);
	void MapIsland(int _startIndex, sf::RenderWindow& window);
	void collapseIslands(sf::RenderWindow& window);

	std::vector<Node*> nodeGrid;
private:
	std::vector<std::vector<Node*>> islandsGrid;

	int gridNodeSize = 32; //each tile is 20x 20
};

