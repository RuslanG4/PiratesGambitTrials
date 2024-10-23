#include "Grid.h"

Grid::Grid(int density, sf::Font& _font)
{
	int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
	int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns

	nodeGrid.reserve(rows * cols); // reserve memory

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int random = std::rand() % 100;
			if (random > density)
			{
				nodeGrid.push_back(new Node(j * gridNodeSize, i * gridNodeSize, gridNodeSize, false)); //pushes a new node with passable x, y, size and noise
			}
			else
			{
				nodeGrid.push_back(new Node(j * gridNodeSize, i * gridNodeSize, gridNodeSize, true)); //pushes a new node with passable x, y, size and noise
			}
			
		}
	}
	//Setup id's first
	int max = rows * cols;
	for (int i = 0; i < max; i++)
	{
		nodeGrid[i]->setID(i);
		addNeighbours(i);
	}
}

void Grid::drawGrid(sf::RenderWindow& _window) const
{
	for(auto node : nodeGrid)
	{
		_window.draw(node->drawableNode);
	}
}

void Grid::addNeighbours(int _currentNodeId) const
{
	const int MAX_ROWS = (SCREEN_HEIGHT / gridNodeSize);
	const int MAX_COLS = (SCREEN_WIDTH / gridNodeSize);

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
			nodeGrid[_currentNodeId]->addNeighbour(nodeGrid[neighbourIndex]);  
		}
	}
}

void Grid::WaveFunctionCollapse(const std::vector<Node*>& _currentIsland, sf::RenderWindow& window)
{
	std::priority_queue <Node*> nodeQueue;
	int id = _currentIsland.at(rand() % _currentIsland.size())->getID();

	Node* start = nodeGrid[id];
	start->m_possibleTiles = { TileType::LAND };
	DetermineTile(start);
	determineTileTexture(start);
	start->setMarked();
	nodeQueue.push(start);

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		Node* currentTop = nodeQueue.top();

		nodeQueue.pop();

		auto neighbours = currentTop->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (!neighbour->getMarked()) {
				if (neighbour->m_possibleTiles.size() > 1 && neighbour->getTileType() != TileType::WATER) {
					// Recalculate the possible tiles for neighbors based on new rules
					DetermineTile(neighbour);
					determineTileTexture(neighbour);
					neighbour->setMarked();
					/*drawGrid(window);
					window.display();
					wait();*/
					nodeQueue.push(neighbour);
				}
			}
		}
	}

}

void Grid::DetermineTile(Node* _currentNode) const
{
	TileType chosenTileOptions = TileType::LAND;
	bool hasWaterNeighbour{ false };
	bool hasSandNeighbour{ false };

	for (auto neighbour : _currentNode->getNeighbours())
	{
		if (neighbour->getTileType() == TileType::WATER)
		{
			hasWaterNeighbour = true;
		}
		else if (neighbour->getTileType() == TileType::SAND)
		{
			hasSandNeighbour = true;
		}
	}

	if (hasWaterNeighbour) {
		if (FollowsWaterPattern(_currentNode))
		{
			chosenTileOptions = { TileType::WATER };
			_currentNode->setLand(false);
		}
		else {
			chosenTileOptions = { TileType::SAND };
		}
	}
	else if (hasSandNeighbour) {
		int random = std::rand() % 100;
		if (random > 70)
		{
			chosenTileOptions = { TileType::GRASSY_LAND };
		}
		else {
			chosenTileOptions = { TileType::LAND };
		}
	}

	_currentNode->setTileType(chosenTileOptions);
}

bool Grid::FollowsWaterPattern(const Node* _currentNode) const
{
	for (const auto& pattern : waterReplacementPatterns)
	{
		if (CheckPattern(_currentNode,pattern))
		{
			return true;
		}
	}
	return false;
}

bool Grid::CheckPattern(const Node* _currentNode, const std::vector<int>& _pattern) const
{
	int patternCount = 0;
	for (int i = 0; i < _pattern.size(); i++)
	{
		if (_pattern[i] < _currentNode->getNeighbours().size()) {
			if (!_currentNode->getNeighbours()[_pattern[i]]->getIsLand())
			{
				patternCount++;
				if (patternCount == _pattern.size())
				{
					return true;
				}
			}
			else {
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	return true;
}

//debug wait timer
void Grid::wait()
{
	int timer = 0;
	bool moveOn = false;
	while (!moveOn)
	{
		timer++;
		if (timer > 1000000)
		{
			moveOn = !moveOn;
		}
	}
}

void Grid::ApplyCellular(int _interations, sf::RenderWindow& m_window)
{
	for(int i =0;i<_interations;i++)
	{
		// Deep copy the grid (create new nodes, not just copy pointers)
		std::vector<Node*> tempGrid;
		for (auto node : nodeGrid)
		{
			Node* newNode = new Node(*node);  // Create a copy of the node
			tempGrid.push_back(newNode);
		}

		for(auto node : tempGrid)
		{
			int wallCount = 0;

			for(auto neighbour : node->getNeighbours())
			{
				if(neighbour->getIsLand())
				{
					wallCount++;
				}
			}
	
			if(wallCount > 4)
			{
				node->drawableNode.setTexture(textureManager.getTexture("sandTile"));
				node->setTileType(TileType::SAND);
				node->setLand(true);
			}else
			{
				node->drawableNode.setTexture(textureManager.getTexture("waterTile"));
				node->setTileType(TileType::WATER);
				node->setLand(false);
			}
		}
		// Now apply changes back to the original nodeGrid
		for (size_t j = 0; j < nodeGrid.size(); j++)
		{
			nodeGrid[j]->setLand(tempGrid[j]->getIsLand());
			nodeGrid[j]->drawableNode.setTexture(*tempGrid[j]->drawableNode.getTexture());
			nodeGrid[j]->setTileType(tempGrid[j]->getTileType());

			//Uncomment for debug
			/*drawGrid(m_window);
			m_window.display();
			wait();*/
		}
		
		// Clean up the temporary grid
		for (auto node : tempGrid)
		{
			delete node;  // Free memory for deep-copied nodes
		}
	}
	FindLand(m_window);
}

//looks for any land in grid
void Grid::FindLand(sf::RenderWindow& m_window)
{
	for(auto node : nodeGrid)
	{
		if(node->getMarked() == false && node->getIsLand())
		{
			MapIsland(node->getID(),m_window);
		}
	}
	collapseIslands(m_window);
}

void Grid::MapIsland(int _startIndex, sf::RenderWindow & window)
{
	std::vector<Node*> currentIsland;
	std::queue <Node*> nodeQueue;
	nodeQueue.push(nodeGrid[_startIndex]);

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		auto neighbours = nodeQueue.front()->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false) {
				neighbour->setMarked();
				if (neighbour->getIsLand()) {
					currentIsland.push_back(neighbour);
					nodeQueue.push(neighbour);
				}
			}
		}
		nodeQueue.pop();
	}
	//add island to storage
	islandsGrid.push_back(currentIsland);
}

void Grid::collapseIslands(sf::RenderWindow& window)
{
	for(auto island : islandsGrid)
	{
		for(auto node : island)
		{
			node->resetMarked();
		}
		if (!island.empty()) {
			WaveFunctionCollapse(island, window);
		}
	}
}

void Grid::determineTileTexture(Node* _node) const
{
	switch (_node->getTileType())
	{
	case WATER:
		_node->drawableNode.setTexture(textureManager.getTexture("waterTile"));
		break;
	case LAND:
		_node->drawableNode.setTexture(textureManager.getTexture("landTile"));
		break;
	case GRASSY_LAND:
		_node->drawableNode.setTexture(textureManager.getTexture("grassyLandTile"));
		break;
	case SAND:
		_node->drawableNode.setTexture(textureManager.getTexture("sandTile"));
		break;
	}
}





