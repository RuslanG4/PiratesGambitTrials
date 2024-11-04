#include "FullMap.h"

FullMap::FullMap(sf::RenderWindow& window, TextureManager& instance, const int& chunkWidth_, const int& chunkHidth_)
{
	initMap(chunkWidth_, chunkHidth_);
	initChunks(instance, window);
	/*int iteration = 0;
	int rand = std::rand() % 35+15;
	int iterss = std::rand() % 4;*/
	//for(int y= 0 ; y < 3; y++) //whole map is 3x3
	//{
	//	for(int x=0;x<3;x++)
	//	{
	//		int height = 576;/* 16 * ((std::rand() % 16  + 16) + 16);*/
	//		int width = 576;/*16 * ((std::rand() % 16+16) + 16);*/
	//		iteration++;
	//		if(iteration == 2 || iteration == 4 || iteration ==9)
	//		{
	//			Grid* chunk = new Grid(70, sf::Vector2f(x * width, y * height), width, height);
	//			chunk->ApplyCellular(7, window);
	//			chunks_.push_back(chunk);
	//		}else
	//		{
	//			Grid* chunk = new Grid(52, sf::Vector2f(x * width, y * height), width, height);
	//			chunk->ApplyCellular(3, window);
	//			chunks_.push_back(chunk);
	//		}
	//	}
	//}
	//int height = 1024;/* 16 * ((std::rand() % 16  + 16) + 16);*/
	//int width = 1024;/*16 * ((std::rand() % 16+16) + 16);*/
	//Grid* chunk = new Grid(70, sf::Vector2f(0 * width, 0 * height), width, height, instance);
	//chunk->ApplyCellular(7, window);
	//chunks_.push_back(chunk);

	//Grid* chunk = new Grid();
	//chunk->DiamondSquare();
	//chunks_.push_back(chunk);

}

void FullMap::initMap(const int& chunksRowAmount_, const int& chunksColAmount_)
{
	chunksRowAmount = chunksRowAmount_; 
	chunksColAmount = chunksColAmount_;
	int rows = CHUNK_NODE_ROWS * chunksRowAmount;  //identifies the amount of rows
	int cols = CHUNK_NODE_COLS * chunksColAmount;  //identifies the amount of columns

	fullMapGrid.reserve(rows * cols); // reserve memory

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			fullMapGrid.push_back(new Node(x * CHUNK_NODE_COLS, y * CHUNK_NODE_ROWS, nodeSize, false));
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
	for (int chunkY = 0; chunkY < chunksColAmount; chunkY++)
	{
		for (int chunkX = 0; chunkX < chunksRowAmount; chunkX++)
		{
			int chunkIndex = chunkY * chunksRowAmount + chunkX;
			std::vector<Node*> chunkNodes;
			addNodesToVector(chunkNodes, chunkX, chunkY);
			Grid* chunk = new Grid(70, instance, chunkNodes);
			chunk->ApplyCellular(7, window);
			chunk->setChunkID(chunkIndex);
			chunks_.push_back(chunk);
		}
	}
}
///Splits larger grid into chunks and assigns those a chunk ID
void FullMap::addNodesToVector(std::vector<Node*>& _vec, int _chunkX, int _chunkY)
{
	int newId = 0;
	for (int y = 0; y < CHUNK_NODE_COLS; y++) {
		for (int x = 0; x < CHUNK_NODE_ROWS; x++) {
			int nodePos = (_chunkX * CHUNK_NODE_COLS + y) * (chunksColAmount * CHUNK_NODE_ROWS) + (_chunkY * CHUNK_NODE_ROWS + x);
			_vec.push_back(fullMapGrid[nodePos]);
			fullMapGrid[nodePos]->setChunkID(newId);
			newId++;
		}
	}
}

void FullMap::addNeighbours(int _currentNodeId) const
{
	const int MAX_ROWS = CHUNK_NODE_ROWS * chunksRowAmount;
	const int MAX_COLS = CHUNK_NODE_COLS * chunksColAmount;

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

void FullMap::render(sf::RenderWindow& window)
{
	for(auto chunk : chunks_)
	{
		chunk->drawGrid(window);
	}
}
