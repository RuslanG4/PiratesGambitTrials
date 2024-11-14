#pragma once
#include"Includes.h"
#include"Node.h"
#include"TextureManager.h"
#include"TileRules.h"

class Grid
{
public:
	Grid(const std::vector<Node*>& gridNodes_);
	~Grid()
	{
		delete this;
	}
	void drawGrid(sf::RenderWindow& _window) const;

	void setChunkID(int id_) { chunkID = id_; }
	int getChunkID() const { return chunkID; }
	sf::Vector2f getMinVector() const { return { static_cast<float>(chunkStartX), static_cast<float>(chunkStartY) }; }
	sf::Vector2f getMaxVector() const { return { static_cast<float>(chunkEndX),static_cast<float>(chunkEndY) }; }

	//Surrounding Nodes for updating
	void searchLocalArea(Node*& _startNode, int iterations_);

	//Debug wait
	void wait(int time);

	//Cellular Automata
	void ApplyCellular(int _interations, sf::RenderWindow& window);

	//Find + Map Islands
	void FindLand(sf::RenderWindow& m_window);
	void MapIsland(int _startIndex, bool saveIslandData, sf::RenderWindow& window);
	void SaveIslandData(sf::RenderWindow& window);
	void removeWorldEdges(Node* _currentNode) const;
	void UnMarkNodes();

	//Tile rules
	void FilterTiles(Node* _currentNode) const;
	int FollowsPatterns(const Node* _currentNode, const std::vector<std::vector<std::pair<int, bool>>>& _pattern) const;
	bool FilterWaterTiles(const Node* _currentNode)const;
	bool filterUndesiredTiles(const Node* _currentNode) const;
	bool CheckPattern(const Node* _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const;


	void replaceUndesiredLand(Node* _node) const;
	void determineTileTexture(Node* _node) const;

	void determineSandTileType(Node* _node) const;
	void determineLandTileType(Node* _node) const;
	void determineWaterTileType(Node* _node) const;

	std::vector<Node*> nodeGrid;

	//clear memory
	void deleteSprites() const;
private:
	std::vector<std::vector<Node*>> islandsGrid;

	int chunkID;

	int chunkStartX, chunkStartY;
	int chunkEndX, chunkEndY;
};

