#pragma once
#include"Includes.h"
#include"Node.h"
#include"TextureManager.h"
#include"TileRules.h"

class Grid
{
public:
	Grid(TextureManager& instance);
	Grid(int density, sf::Vector2f _startPoint, int max_width, int max_height, TextureManager& instance);
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

	//Tile rules
	void FilterTiles(Node* _currentNode);
	int FollowsPatterns(const Node* _currentNode, const std::vector<std::vector<std::pair<int, bool>>> _pattern) const;
	bool FilterWaterTiles(const Node* _currentNode)const;
	bool filterUndesiredTiles(const Node* _currentNode) const;
	bool CheckPattern(const Node* _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const;


	void replaceUndesiredLand(Node* _node) const;
	void determineTileTexture(Node* _node) const;

	void determineSandTileType(Node* _node) const;
	void determineLandTileType(Node* _node) const;
	void determineWaterTileType(Node* _node) const;

	std::vector<Node*> nodeGrid;
private:
	TextureManager& textureManager;

	std::vector<std::vector<Node*>> islandsGrid;

	int gridNodeSize = 32; //each tile is 32x 32

	int mapWidth;
	int mapHeight;
};

