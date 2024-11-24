#pragma once
#include"Grid.h"

class FullMap
{
public:
	FullMap() {};
	FullMap(sf::RenderWindow & window, const int& mapSize_);

	void initMap(const int& mapSize_);
	void initChunks(sf::RenderWindow& window);
	std::vector<Node*> populateChunk(int _chunkX, int _chunkY, int _density) const;

	void addNeighbours(int _currentNodeId) const;

	void render(sf::RenderWindow& window) const;

	const std::vector<std::unique_ptr<Grid>>& getChunks() const { return chunks_; };
	std::vector<Node*> getFullMap() { return fullMapGrid; };

	static void configureNode(Node* _node, int _density);
private:
	std::vector<std::unique_ptr<Grid>> chunks_;
	//std::vector<Grid*> chunks_;

	sf::Sprite fullMapSprite;
	sf::Texture fullMapTexture;
	

	int mapSize;

	std::vector<Node*> fullMapGrid;

	int nodeSize = 32;
};

