#pragma once
#include"Includes.h"
#include"Node.h"
#include"TextureManager.h"
#include"TileRules.h"

class Grid
{
public:
	Grid();
	Grid(int density, sf::Vector2f _startPoint);
	void drawGrid(sf::RenderWindow& _window) const;
	void addNeighbours(int _currentNodeId) const ;

	//Debug wait
	void wait(int time);

	//Cellular Automata
	void ApplyCellular(int _interations, sf::RenderWindow& window);

	//Find + Map Islands
	void FindLand(sf::RenderWindow& m_window);
	void MapIsland(int _startIndex, bool saveIslandData, sf::RenderWindow& window);
	void SaveIslandData(sf::RenderWindow& window);
	void removeWorldEdges(Node* _currentNode);

	//WFC
	void collapseIsland(std::vector<Node*>& _currentIsland, sf::RenderWindow& window);
	void WaveFunctionCollapse(const std::vector<Node*>& _currentIsland, sf::RenderWindow& window);

	//Tile rules
	int FollowsSandPatterns(const Node* _currentNode) const;
	bool filterUndesiredTiles(const Node* _currentNode) const;
	bool CheckPattern(const Node* _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const;

	void setTileTextures(std::vector<Node*>& _island);
	void replaceUndesiredLand(Node* _code);
	void determineTileTexture(Node* _node) const;

	std::vector<Node*> nodeGrid;
private:
	TextureManager& textureManager = TextureManager::getInstance();

	std::vector<std::vector<Node*>> islandsGrid;

	int gridNodeSize = 32; //each tile is 32x 32
};

