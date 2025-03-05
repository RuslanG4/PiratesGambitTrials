#pragma once
#include"Grid.h"

///<summary>
/// Generates nodes for the entire playable map and assigns chunks
///</summary>
class FullMap
{
public:
	FullMap(const int& mapSize_, const std::shared_ptr<Player>& _playerRef);

	void initMap(const int& mapSize_);
	void initChunks();
	std::vector<std::shared_ptr<Node>> populateChunk(int _chunkX, int _chunkY, int _density) const;

	void addNeighbours(int _currentNodeId) const;

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	const std::vector<std::unique_ptr<Grid>>& getChunks() const { return chunks_; };
	const std::vector<std::shared_ptr<Node>>& getFullMap() const { return fullMapGrid; };

	static void configureNode(const std::weak_ptr<Node>& _node, int _density);
private:
	std::shared_ptr<Player> playerRef;
	std::vector<std::shared_ptr<Node>> fullMapGrid;
	std::vector<std::unique_ptr<Grid>> chunks_;

	int mapSize;
	int nodeSize = 32; //size of nodes
};

