#include "FullMap.h"

FullMap::FullMap(sf::RenderWindow& window, TextureManager& instance, const int& mapSize_)
{
	initMap(mapSize_);
	initChunks(instance, window);
}

void FullMap::initMap(const int& mapSize_)
{
	mapSize = mapSize_;
	int rows = CHUNK_NODE_ROWS * mapSize;  //identifies the amount of rows
	int cols = CHUNK_NODE_COLS * mapSize;  //identifies the amount of columns

	fullMapGrid.reserve(rows * cols); // reserve memory

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			fullMapGrid.push_back(new Node(x * nodeSize, y * nodeSize, nodeSize, false));
		}
	}
	//Setup id's first
	int max = rows * cols;
	for (int i = 0; i < max; i++)
	{
		fullMapGrid[i]->setID(i);
		addNeighbours(i);
	}
}

void FullMap::initChunks(TextureManager& instance, sf::RenderWindow& window)
{
	for (int chunkY = 0; chunkY < mapSize; chunkY++)
	{
		for (int chunkX = 0; chunkX < mapSize; chunkX++)
		{
			int chunkIndex = chunkY * mapSize + chunkX;

			std::vector<Node*> chunkNodes = populateChunk(chunkX, chunkY, 60);
			Grid* chunk = new Grid(instance, chunkNodes);
			chunk->ApplyCellular(2, window);
			chunk->setChunkID(chunkIndex);
			chunks_.push_back(chunk);
		}
	}
}
///Splits larger grid into chunks and assigns those a chunk ID
std::vector<Node*> FullMap::populateChunk(int _chunkX, int _chunkY, int _density) const 
{
	std::vector<Node*> chunkNodes;
	int newId = 0;
	for (int y = 0; y < CHUNK_NODE_COLS; y++) {
		for (int x = 0; x < CHUNK_NODE_ROWS; x++) {
			int nodePos = (_chunkX * CHUNK_NODE_COLS + y) * (mapSize * CHUNK_NODE_ROWS) + (_chunkY * CHUNK_NODE_ROWS + x);

			configureNode(fullMapGrid[nodePos], _density);

			chunkNodes.push_back(fullMapGrid[nodePos]);
			fullMapGrid[nodePos]->setChunkID(newId);
			newId++;
		}
	}
	return chunkNodes;
}

void FullMap::addNeighbours(int _currentNodeId) const
{
	const int MAX_ROWS = CHUNK_NODE_ROWS * mapSize;
	const int MAX_COLS = CHUNK_NODE_COLS * mapSize;

	int row = _currentNodeId / MAX_COLS;
	int col = _currentNodeId % MAX_COLS;
	int neighbourIndex = -1;

	//This neighbour algoritihim prioritises vertical/hjorizontal then diagonal
	std::array<int, 8> directionOrder
	{
		0,1,2,3,5,6,7,8 //exclude 4 since that is our cell
	};
	for (auto& direction : directionOrder) {

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {
			neighbourIndex = n_row * MAX_COLS + n_col;
			fullMapGrid[_currentNodeId]->addNeighbour(fullMapGrid[neighbourIndex]);
		}
	}
}

void FullMap::render(sf::RenderWindow& window) const
{
	for (auto chunk : chunks_)
	{
		chunk->drawGrid(window);
	}
}

void FullMap::configureNode(Node* _node, int _density)
{
	int random = std::rand() % 100;
	if (random > _density)
	{
		_node->setLand(false);
	}
	else
	{
		_node->setLand(true);
	}
}


