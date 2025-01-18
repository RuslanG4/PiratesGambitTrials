#pragma once
#include"Includes.h"
#include"Node.h"
#include"TextureManager.h"
#include"TileRules.h"
#include"Island.h"

///<summary>
/// Individual chunks in game world, responsible for procedural generation, and holding generated islands as well as nodes inside the chunk
///</summary>
class Grid
{
public:
	Grid(const std::vector<std::shared_ptr<Node>>& gridNodes_);

	void drawGrid(const std::unique_ptr<sf::RenderWindow>& window) const;
	void drawGameObject(const std::unique_ptr<sf::RenderWindow>& window) const;

	void updateIslands() const;
	const std::vector<std::unique_ptr<Island>>& getIslands() const { return islands; }

	void setChunkID(int id_) { chunkID = id_; }
	int getChunkID() const { return chunkID; }
	sf::Vector2f getMinVector() const { return { static_cast<float>(chunkStartX), static_cast<float>(chunkStartY) }; }
	sf::Vector2f getMaxVector() const { return { static_cast<float>(chunkEndX),static_cast<float>(chunkEndY) }; }

	//Debug wait
	void wait(int time);

	//Cellular Automata
	void ApplyCellular(int _interations, const std::unique_ptr<sf::RenderWindow>& window);

	//Find + Map Islands
	void FindLand(const std::unique_ptr<sf::RenderWindow>& window);
	void MapIsland(int _startIndex, bool saveIslandData, const std::unique_ptr<sf::RenderWindow>& window);
	void SaveIslandData(const std::unique_ptr<sf::RenderWindow>& window);
	void removeWorldEdges(std::shared_ptr<Node>& _currentNode) const;
	void UnMarkNodes() const;

	//Tile rules
	void FilterTiles(std::shared_ptr<Node>& _currentNode) const;
	int FollowsPatterns(const std::shared_ptr<Node>& _currentNode, const std::vector<std::vector<std::pair<int, bool>>>& _pattern) const;
	bool FilterWaterTiles(const std::shared_ptr<Node>& _currentNode)const;
	bool filterUndesiredTiles(const std::shared_ptr<Node>& _currentNode) const;
	bool CheckPattern(const std::shared_ptr<Node>& _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const;

	//removes undesired jutting tiles
	void replaceUndesiredLand(std::shared_ptr<Node>& _node) const;
	//sets individual node texture
	void determineTileTexture(const std::shared_ptr<Node>& _node) const;

	//determines whether tile is sand land or water
	void determineSandTileType(const std::shared_ptr<Node>& _node) const;
	void determineLandTileType(const std::shared_ptr<Node>& _node) const;
	void determineWaterTileType(const std::shared_ptr<Node>& _node) const;

	std::vector<std::shared_ptr<Node>> nodeGrid;

private:
	//std::vector<std::vector<Node*>> islandsGrid;

	std::vector<std::unique_ptr<Island>> islands;

	int chunkID;

	int chunkStartX, chunkStartY;
	int chunkEndX, chunkEndY;
};

