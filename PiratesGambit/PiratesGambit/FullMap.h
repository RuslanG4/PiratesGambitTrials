#pragma once
#include"Grid.h"

class FullMap
{
public:
	FullMap(sf::RenderWindow & window, TextureManager& instance, const int& chunksRowAmount_, const int& chunksColAmount_);
	~FullMap();

	void initMap(const int& chunkWidth_, const int& chunkHidth_);
	void initChunks(TextureManager& instance, sf::RenderWindow& window);
	void addNodesToVector(std::vector<Node*>& _vec, int _chunkX, int _chunkY);

	void addNeighbours(int _currentNodeId) const;

	void update();
	void render(sf::RenderWindow& window);

	std::vector<Grid*> getChunks() { return chunks_; };
	std::vector<Node*> getFullMap() { return fullMapGrid; };
private:
	std::vector<Grid*> chunks_;

	int chunksRowAmount, chunksColAmount;

	std::vector<Node*> fullMapGrid;

	int nodeSize = 24;
};

