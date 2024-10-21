#include "Grid.h"

Grid::Grid(int density, sf::Font& _font)
{
	int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
	int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int random = std::rand() % 100;
			bool isWall;
			if (random > density)
			{
				isWall = false;
			}
			else
			{
				isWall = true;
			}
			nodeGrid.push_back(new Node(j * gridNodeSize, i * gridNodeSize, gridNodeSize, _font, isWall)); //pushes a new node with passable and x and y and gives id
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

void Grid::createGrid(sf::Font& _font)
{
	//int rows = SCREEN_HEIGHT / gridNodeSize;  //identifies the amount of rows
	//int cols = SCREEN_WIDTH / gridNodeSize;  //identifies the amount of columns
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < cols; j++)
	//	{
	//		nodeGrid.push_back(new Node( j * gridNodeSize, i * gridNodeSize, gridNodeSize, _font)); //pushes a new node with passable and x and y and gives id
	//	}
	//}
	////Setup id's first
	//int max = rows * cols;
	//for (int i = 0; i < max; i++)
	//{
	//	nodeGrid[i]->setID(i);
	//	addNeighbours(i);
	//}
};

void Grid::drawGrid(sf::RenderWindow& _window)
{
	for(auto node : nodeGrid)
	{
		_window.draw(node->drawableNode);
		if (node->drawn == false) {
			_window.draw(node->nodeCostText);
		}
	}
}

void Grid::addNeighbours(int _currentNodeId)
{
	const int MAX_ROWS = (SCREEN_HEIGHT / gridNodeSize);
	const int MAX_COLS = (SCREEN_WIDTH / gridNodeSize);

	int row = _currentNodeId / MAX_COLS;
	int col = _currentNodeId % MAX_COLS;
	int neighbourIndex = -1;

	//This neighbour algoritihim prioritises vertical/hjorizontal then diagonal
	std::array<int, 9> directionOrder
	{
		1,3,5,7,0,2,6,8 //exclude 4 since that is our cell
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

void Grid::collapse(sf::RenderWindow& window)
{
	currentStartNode = 1270;

	std::priority_queue < Node*, std::vector<Node*>, Compare> nodeQueue;

	
	nodeGrid[currentStartNode]->setMarked();
	nodeGrid[currentStartNode]->m_possibleTiles = { NodeType::LAND };
	nodeGrid[currentStartNode]->determineEntropy();

	nodeQueue.push(nodeGrid[currentStartNode]);

	int counter{ 0 };

	// loop through the queue while there are nodes in it.
	while (nodeQueue.size() != 0)
	{
		Node* currentTop = nodeQueue.top();

		currentTop->determineTile();
		nodeGrid[currentStartNode]->determineEntropy();

		drawGrid(window);
		window.display();
		wait();

		NodeType collapsedTile = *currentTop->m_possibleTiles.begin();

		nodeQueue.pop();

		// add all of the child nodes that have not been 
		// marked into the queue
		auto neighbours = currentTop->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false)
			{
				// mark the node and add it to the queue.
				neighbour->setMarked();

				std::unordered_set<NodeType> newPossibleTiles;

				for (NodeType tile : neighbour->m_possibleTiles) {
					if (std::find(nodeRules[collapsedTile].begin(), nodeRules[collapsedTile].end(), tile) != nodeRules[collapsedTile].end()) {
						newPossibleTiles.insert(tile);
					}
				}

				neighbour->m_possibleTiles = newPossibleTiles;
				neighbour->determineEntropy();
				nodeQueue.push(neighbour);
			}
		}
	}

}

void Grid::propogate(Node* _node)
{
}

void Grid::wait()
{
	int timer = 0;
	bool moveOn = false;
	while (!moveOn)
	{
		timer++;
		if (timer > 10000000)
		{
			moveOn = !moveOn;
		}
	}
}

void Grid::DiamondSquare()
{

}

void Grid::ApplyCelular(int _interations, sf::RenderWindow& m_window)
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
				if(neighbour->isWall)
				{
					wallCount++;
				}
			}
	
			if(wallCount > 4)
			{
				node->drawableNode.setFillColor(sf::Color::Yellow);
				node->isWall = true;
			}else
			{
				node->drawableNode.setFillColor(sf::Color::Blue);
				node->isWall = false;
			}
		}
		// Now apply changes back to the original nodeGrid
		for (size_t j = 0; j < nodeGrid.size(); j++)
		{
			nodeGrid[j]->isWall = tempGrid[j]->isWall;
			nodeGrid[j]->drawableNode.setFillColor(tempGrid[j]->drawableNode.getFillColor());
		}
	/*	drawGrid(m_window);
		m_window.display();
		wait();*/
		// Clean up the temporary grid
		for (auto node : tempGrid)
		{
			delete node;  // Free memory for deep-copied nodes
		}
	}
	FindLand(m_window);
}

void Grid::FindLand(sf::RenderWindow& m_window)
{
	std::queue <Node*> nodeQueue;

	nodeGrid[lastWaterIndex]->setMarked();

	nodeQueue.push(nodeGrid[lastWaterIndex]);

		// loop through the queue while there are nodes in it.
	while (nodeQueue.size() != 0)
	{
		//nodeQueue.front()->drawableNode.setFillColor(sf::Color::Red);
			// add all of the child nodes that have not been 
			// marked into the queue
		auto neighbours = nodeQueue.front()->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false) {
				neighbour->setMarked();
				if (neighbour->isWall) {
					lastWaterIndex = nodeQueue.front()->getID();
					MapIsland(neighbour->getID());
					break;
					/*islandGrid.push_back(neighbour);
					nodeQueue.push(neighbour);*/
				}
				nodeQueue.push(neighbour);
			}
		}
		nodeQueue.pop();
	}
}
void Grid::MapIsland(int _startIndex)
{
	std::vector<Node*> currentIsland;
	std::queue <Node*> nodeQueue;
	nodeQueue.push(nodeGrid[_startIndex]);

	// loop through the queue while there are nodes in it.
	while (nodeQueue.size() != 0)
	{
		//nodeQueue.front()->drawableNode.setFillColor(sf::Color::Green);
			// add all of the child nodes that have not been 
			// marked into the queue
		nodeQueue.front()->drawableNode.setFillColor(sf::Color::Green);
		auto neighbours = nodeQueue.front()->getNeighbours();

		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false) {
				neighbour->setMarked();
				if (neighbour->isWall) {
					currentIsland.push_back(neighbour);
					nodeQueue.push(neighbour);
				}
			}
		}
		nodeQueue.pop();
	}

	islandsGrid.push_back(currentIsland);
}




