#pragma once
#include"Grid.h"

class FullMap
{
public:
	FullMap(sf::RenderWindow & window, const int& mapSize_);
	~FullMap();

	void initMap(const int& mapSize_);
	void initChunks(sf::RenderWindow& window);
	std::vector<Node*> populateChunk(int _chunkX, int _chunkY, int _density) const;

	void addNeighbours(int _currentNodeId) const;

	void render(sf::RenderWindow& window) const;

	std::vector<Grid*> getChunks() { return chunks_; };
	std::vector<Node*> getFullMap() { return fullMapGrid; };

	static void configureNode(Node* _node, int _density);
private:
	std::vector<Grid*> chunks_;

	sf::Sprite fullMapSprite;
	sf::Texture fullMapTexture;
	

	int mapSize;

	std::vector<Node*> fullMapGrid;

	int nodeSize = 32;
};

