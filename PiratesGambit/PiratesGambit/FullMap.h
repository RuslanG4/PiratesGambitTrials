#pragma once
#include"Grid.h"

///<summary>
/// Generates nodes for the entire playable map and assigns chunks
///</summary>
class FullMap
{
public:
	FullMap() {};
	FullMap(sf::RenderWindow & window, const int& mapSize_);

	void initMap(const int& mapSize_);
	void initChunks(sf::RenderWindow& window);
	std::vector<std::shared_ptr<Node>> populateChunk(int _chunkX, int _chunkY, int _density) const;

	void addNeighbours(int _currentNodeId) const;

	void render(sf::RenderWindow& window) const;

	const std::vector<std::unique_ptr<Grid>>& getChunks() const { return chunks_; };
	const std::vector<std::shared_ptr<Node>>& getFullMap() const { return fullMapGrid; };

	static void configureNode(const std::weak_ptr<Node>& _node, int _density);
private:
	std::vector<std::shared_ptr<Node>> fullMapGrid;
	std::vector<std::unique_ptr<Grid>> chunks_;

	int mapSize;
	int nodeSize = 32; //size of nodes
};

