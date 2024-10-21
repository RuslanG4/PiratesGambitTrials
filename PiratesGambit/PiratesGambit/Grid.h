#pragma once
#include"Includes.h"
#include"Node.h"

class Compare {
public:
	bool operator()(Node* const a, Node* const b) {
		return a->entropy < b->entropy;
	}
};

class Grid
{
public:
	Grid(sf::Font& _font)
	{
		createGrid(_font);
	};
	Grid(int density,sf::Font& _font);
	void createGrid(sf::Font& _font);
	void drawGrid(sf::RenderWindow& _window);
	void addNeighbours(int _currentNodeId);
	int const getNodeSize() const { return gridNodeSize; };

	void pathFind();

	void collapse(sf::RenderWindow& window);
	void propogate(Node* _node);

	void wait();

	void DiamondSquare();
	void ApplyCelular(int _interations, sf::RenderWindow& window);
	void FindLand(sf::RenderWindow& m_window);
	void MapIsland(int _startIndex);

	std::vector<Node*> nodeGrid;
private:
	std::vector<std::vector<Node*>> islandsGrid;

	bool foundLand{ false };
	int lastWaterIndex{ 0 };

	int landCount=0, sandCount=0, waterCount=0;

	int currentStartNode{ -1 };
	int currentEndNode{ -1 };

	int gridNodeSize = 32; //each tile is 20x 20

	sf::Clock timer;

	int maxLand = 400;
	int maxSand = 200;

	std::map<NodeType, std::vector<NodeType>> nodeRules = {
{ WATER, { WATER } }, // Water can touch water and sand
{ SAND, { WATER } }, // Sand can touch sand, land, and water
{ LAND, { LAND, SAND } } // Land can touch land and sand
	};
};

