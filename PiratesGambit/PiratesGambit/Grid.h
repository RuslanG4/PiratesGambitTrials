#pragma once
#include"Includes.h"
#include"Node.h"
#include"TextureManager.h"

class Grid
{
public:
	Grid(int density,sf::Font& _font);
	void drawGrid(sf::RenderWindow& _window) const;
	void addNeighbours(int _currentNodeId) const ;

	//Debug wait
	void wait();

	//Cellular Automata
	void ApplyCellular(int _interations, sf::RenderWindow& window);

	//Find + Map Islands
	void FindLand(sf::RenderWindow& m_window);
	void MapIsland(int _startIndex, sf::RenderWindow& window);

	//WFC
	void collapseIslands(sf::RenderWindow& window);
	void WaveFunctionCollapse(const std::vector<Node*>& _currentIsland, sf::RenderWindow& window);

	//Tile rules
	bool FollowsWaterPattern(const Node* _currentNode) const;
	bool CheckPattern(const Node* _currentNode, const std::vector<int>& _pattern) const;
	void DetermineTile(Node* _currentNode)const;
	void determineTileTexture(Node* _node) const;

	std::vector<Node*> nodeGrid;
private:
	TextureManager& textureManager = TextureManager::getInstance();

	std::vector<std::vector<Node*>> islandsGrid;

	std::vector<std::vector<int>> waterReplacementPatterns
	{
		{ 1,3,6 }, 
	{ 1,3,4 },  
	{ 3,4,6 }, 
	{ 1,4,6 } 
	};

	int gridNodeSize = 16; //each tile is 32x 32
};

