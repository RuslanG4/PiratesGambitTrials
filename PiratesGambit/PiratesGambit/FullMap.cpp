#include "FullMap.h"

FullMap::FullMap(const int& mapSize_, const std::shared_ptr<Player>& _playerRef)
{
	playerRef = _playerRef;
	initMap(mapSize_);
	initChunks();
}

/// <summary>
/// Generates map based on size given with set chunk sizes
/// </summary>
/// <param name="mapSize_">how big you want map</param>
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
			NodeData data;
			data.gridX = x * nodeSize;
			data.gridY = y * nodeSize;
			data.size = nodeSize;
			fullMapGrid.push_back(std::make_shared<Node>(data));
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

/// <summary>
/// Seperates the map into chunks for efficiency
/// </summary>
/// <param name="window"></param>
void FullMap::initChunks()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> bigIslandDist(65, 70); 
	std::uniform_int_distribution<int> smallIslandDist(50, 58);
	std::uniform_int_distribution<int> cellularExtentBig(6, 7);
	std::uniform_int_distribution<int> cellularExtentSmall(3, 4);

	std::vector<int> availableBigIslandIndices = { 0, 1, 2, 3, 4 };

	int cellularExtent = 0;

	for (int chunkY = 0; chunkY < mapSize; chunkY++)
	{
		bool isBigIsland = false;
		std::uniform_int_distribution<int> bigIslandIndexDist(0, availableBigIslandIndices.size() - 1);
		int index = bigIslandIndexDist(gen);
		int randomCol = availableBigIslandIndices[index];

		for (int chunkX = 0; chunkX < mapSize; chunkX++)
		{
			int chunkIndex = chunkY * mapSize + chunkX;
			int amount = 0;

			if (!availableBigIslandIndices.empty() && chunkX == randomCol && !isBigIsland)
			{
				availableBigIslandIndices.erase(availableBigIslandIndices.begin() + index);

				amount = bigIslandDist(gen);
				isBigIsland = true;

				cellularExtent = cellularExtentBig(gen);
			}
			else
			{
				amount = smallIslandDist(gen);
				cellularExtent = cellularExtentSmall(gen);
			}

			std::vector<std::shared_ptr<Node>> chunkNodes = populateChunk(chunkX, chunkY, amount);

			std::unique_ptr<Grid> chunk = std::make_unique<Grid>(chunkNodes, playerRef);
			chunk->ApplyCellular(cellularExtent);
			chunk->setChunkID(chunkIndex);

			chunks_.push_back(std::move(chunk));
		}
	}
}



///<summary>
/// Splits larger grid into chunks and assigns those a chunk ID
///</summary>
std::vector<std::shared_ptr<Node>> FullMap::populateChunk(int _chunkX, int _chunkY, int _density) const
{
	std::vector<std::shared_ptr<Node>> chunkNodes;
	int newId = 0;
	for (int y = 0; y < CHUNK_NODE_COLS; y++) {
		for (int x = 0; x < CHUNK_NODE_ROWS; x++) {
			int nodePos = (_chunkX * CHUNK_NODE_COLS + y) * (mapSize * CHUNK_NODE_ROWS) + (_chunkY * CHUNK_NODE_ROWS + x);

			configureNode(fullMapGrid[nodePos], _density); //set node to land/water 

			chunkNodes.push_back(fullMapGrid[nodePos]);
			fullMapGrid[nodePos]->setChunkID(newId);
			newId++;
		}
	}
	return chunkNodes;
}

///<summary>
/// adds neighbours to every node
///</summary>
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

			fullMapGrid[_currentNodeId]->addNeighbour(fullMapGrid[neighbourIndex], direction);
			fullMapGrid[_currentNodeId]->getNodeData().neighbourIDs.emplace_back(neighbourIndex,direction);
		}
	}
}

void FullMap::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for (auto& chunk : chunks_)
	{
		chunk->drawGrid(window);
	}
}

///<summary>
/// Determines if node should be land or water for algorithms
///</summary>
void FullMap::configureNode(const std::weak_ptr<Node>& _node, int _density)
{
	int random = std::rand() % 100;
	if (random > _density)
	{
		_node.lock()->setLand(false);
	}
	else
	{
		_node.lock()->setLand(true);
	}
}


