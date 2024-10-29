#include "Grid.h"

Grid::Grid()
{
	int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
	int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns

	nodeGrid.reserve(rows * cols); // reserve memory

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++){
			nodeGrid.push_back(new Node(j * gridNodeSize, i * gridNodeSize, gridNodeSize, false)); //pushes a new node with passable x, y, size and noise
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

Grid::Grid(int density, sf::Vector2f _startPoint)
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
				nodeGrid.push_back(new Node(_startPoint.x + (j * gridNodeSize), _startPoint.y + (i * gridNodeSize), gridNodeSize, false)); //pushes a new node with passable x, y, size and noise
			}
			else
			{
				nodeGrid.push_back(new Node(_startPoint.x + (j * gridNodeSize), _startPoint.y + (i * gridNodeSize), gridNodeSize, true)); //pushes a new node with passable x, y, size and noise
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
		_window.draw(node->waterBackSprite);
		_window.draw(node->drawableNode);
		if(node->drawDebug)
		{
			_window.draw(node->debugShape);
		}
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

	start->setMarked();
	nodeQueue.push(start);

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		Node* currentTop = nodeQueue.top();

		determineTileTexture(currentTop);

		nodeQueue.pop();

		auto neighbours = currentTop->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (!neighbour->getMarked()) {
				if (neighbour->m_possibleTiles.size() > 1 && neighbour->getTileType() != TileType::WATER) {
					// Recalculate the possible tiles for neighbors based on new rules
					neighbour->setMarked();
					neighbour->drawDebug = false;

					nodeQueue.push(neighbour);

				}
			}
		}

	}
}

//Checks sand tile texture rules
int Grid::FollowsSandPatterns(const Node* _currentNode) const
{
	for(int currentPattern = 0; currentPattern < sandCornerPatterns.size(); currentPattern++)
	{
		if (CheckPattern(_currentNode, sandCornerPatterns[currentPattern]))
		{
			return currentPattern;
		}
	}
	return -1;
}

//checks undesired tile rules
bool Grid::filterUndesiredTiles(const Node* _currentNode) const
{
	for (const auto& pattern : undesiredTiles)
	{
		if (CheckPattern(_currentNode, pattern))
		{
			return true;
		}
	}
	return false;
}

//takes in patterns and corss checks neighbours to see if match
bool Grid::CheckPattern(const Node* _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const
{
	int patternCount = 0;
	for (int i = 0; i < _pattern.size(); i++)
	{
		if (_currentNode->getNeighbours().size() > 5) {
			if (_currentNode->getNeighbours()[_pattern[i].first]->getIsLand() == _pattern[i].second)
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
			return false;
		}
	}
	return false;
}

//debug wait timer
void Grid::wait(int time)
{
	int timer = 0;
	bool moveOn = false;
	while (!moveOn)
	{
		timer++;
		if (timer > time)
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
				node->drawableNode.setTexture(textureManager.getTexture("landTile"));
				node->setTileType(TileType::LAND);
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
			wait(1);*/
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
		/*drawGrid(m_window);
		m_window.display();
		wait(1);*/
		node->drawDebug = true;
		if(node->getMarked() == false && node->getIsLand())
		{
			MapIsland(node->getID(),false ,m_window);
		}
	}
	for(auto node : nodeGrid)
	{
		node->resetMarked();
	}
	SaveIslandData(m_window);
	for(auto island: islandsGrid)
	{
		collapseIsland(island, m_window);
	}
}

void Grid::MapIsland(int _startIndex,bool saveIslandData, sf::RenderWindow & window)
{
	std::vector<Node*> currentIsland;
	std::queue <Node*> nodeQueue;

	nodeQueue.push(nodeGrid[_startIndex]);

	nodeQueue.front()->setMarked();
	nodeQueue.front()->debugShape.setFillColor(sf::Color(23,23,23,66));
	nodeQueue.front()->drawDebug = true;

	if (filterUndesiredTiles(nodeQueue.front()))
	{
		replaceUndesiredLand(nodeQueue.front());
	}

	currentIsland.push_back(nodeQueue.front());

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		if (filterUndesiredTiles(nodeQueue.front()))
		{
			replaceUndesiredLand(nodeQueue.front());
		}
		if(nodeQueue.front()->getNeighbours().size() < 8)
		{
			removeWorldEdges(nodeQueue.front());
		}
		nodeQueue.front()->debugShape.setFillColor(sf::Color(123, 123, 123, 66));
		/*drawGrid(window);
		window.display();
		wait(1);*/
		auto neighbours = nodeQueue.front()->getNeighbours();
		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false) {
				neighbour->setMarked();
				if (neighbour->getIsLand()) {
					
					currentIsland.push_back(neighbour);
					nodeQueue.push(neighbour);


					neighbour->debugShape.setFillColor(sf::Color(23, 23, 23, 66));
					neighbour->drawDebug = true;
					/*drawGrid(window);
					window.display();
					wait(1);*/
				}
			}
		}
		
		nodeQueue.pop();
		
	}
	if(saveIslandData)
	{
		islandsGrid.push_back(currentIsland);
	}
	
}

//Saves islands to a node vector for future use
void Grid::SaveIslandData(sf::RenderWindow& window)
{
	for (auto node : nodeGrid)
	{
		if (node->getMarked() == false && node->getIsLand())
		{
			MapIsland(node->getID(),true, window);
		}
	}
}

//removes edge tiles so chunk edge is always water
void Grid::removeWorldEdges(Node* _currentNode)
{
	_currentNode->setTileType(TileType::WATER);
	_currentNode->setLand(false);
	determineTileTexture(_currentNode);
}

//call to filter tiles
void Grid::collapseIsland(std::vector<Node*>& _currentIsland, sf::RenderWindow& window)
{
	WaveFunctionCollapse(_currentIsland, window);
	setTileTextures(_currentIsland);
}

//sets tiles based of wfc 
void Grid::setTileTextures(std::vector<Node*>& _island)
{
	for (auto node : _island)
	{
		determineTileTexture(node);
	}
}

//removes edge cases of single nodes sticking out, expands on them
void Grid::replaceUndesiredLand(Node* _code)
{
	_code->setLand(true);
	_code->setTileType(TileType::LAND);
	_code->drawableNode.setTexture(textureManager.getTexture("landTile"));
	for (auto neigh : _code->getNeighbours())
	{
		neigh->resetMarked();
		neigh->setLand(true);
		neigh->setTileType(TileType::LAND);
		neigh->drawableNode.setTexture(textureManager.getTexture("landTile"));
	}
}

//set texture 
void Grid::determineTileTexture(Node* _node) const
{
	int random = std::rand() % 100;
	switch (_node->getTileType())
	{
	case WATER:
		_node->drawableNode.setTexture(textureManager.getTexture("waterTile"));
		break;
	case GRASSY_LAND:
		_node->drawableNode.setTexture(textureManager.getTexture("grassyLandTile"));
		break;
	case LAND:
		switch(FollowsSandPatterns(_node))
		{
		case -1:
			if (random > 70)
			{
				_node->setTileType(TileType::GRASSY_LAND);
				determineTileTexture(_node);
			}
			else {
				_node->drawableNode.setTexture(textureManager.getTexture("landTile"));
			}
			
			break;
		case 0:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("TLsandTile"));
			break;
		case 1:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("TRsandTile"));
			break;
		case 2:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("BRsandTile"));
			break;
		case 3:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("BLsandTile"));
			break;
		case 4:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("flatTop"));
			break;
		case 5:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("flatBottom"));
			break;
		case 6:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("flatRight"));
			break;
		case 7:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("flatLeft"));
			break;
		case 8:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("LLSANDTL"));
			break;
		case 9:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("LLSANDBL"));
			break;
		case 10:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("LLSANDTR"));
			break;
		case 11:
			_node->setWaterTexture(textureManager.getTexture("waterTile"));
			_node->drawableNode.setTexture(textureManager.getTexture("LLSANDBR"));
			break;
		}
		break;
	}
}





