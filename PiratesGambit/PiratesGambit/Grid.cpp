#include "Grid.h"

Grid::Grid(const std::vector<Node*>& gridNodes_) : nodeGrid(gridNodes_)
{
	chunkStartX = nodeGrid[0]->getPosition().x;
	chunkEndX = nodeGrid[nodeGrid.size() - 1]->getPosition().x + (nodeGrid[0]->getSize());

	chunkStartY = nodeGrid[0]->getPosition().y;
	chunkEndY = nodeGrid[nodeGrid.size() - 1]->getPosition().y + (nodeGrid[0]->getSize());
}

void Grid::drawGrid(sf::RenderWindow& _window) const
{
	for(auto node : nodeGrid)
	{
		if(node->waterBackSprite && node->drawableNode)
		{
			_window.draw(*(node->waterBackSprite));
			_window.draw(*(node->drawableNode));
		}
		_window.draw(*(node->debugShape));
	}
}

void Grid::FilterTiles(Node* _currentNode) const
{
	if (filterUndesiredTiles(_currentNode))
	{
		replaceUndesiredLand(_currentNode);
	}
	if (_currentNode->getNeighbours().size() < 8)
	{
		removeWorldEdges(_currentNode);
	}
	determineLandTileType(_currentNode);
	determineSandTileType(_currentNode);
	determineWaterTileType(_currentNode);
	determineTileTexture(_currentNode);
}

//Checks sand tile texture rules
int Grid::FollowsPatterns(const Node* _currentNode, const std::vector<std::vector<std::pair<int, bool>>>& _pattern) const
{
	for(int currentPattern = 0; currentPattern < _pattern.size(); currentPattern++)
	{
		if (CheckPattern(_currentNode, _pattern[currentPattern]))
		{
			return currentPattern;
		}
	}
	return -1;
}

bool Grid::FilterWaterTiles(const Node* _currentNode) const
{
	return std::ranges::any_of(undesiredLandTiles, [&](const auto& pattern) {
		return CheckPattern(_currentNode, pattern);
		});
}

//checks undesired tile rules
bool Grid::filterUndesiredTiles(const Node* _currentNode) const
{
	return std::ranges::any_of(undesiredTiles, [&](const auto& pattern) {
		return CheckPattern(_currentNode, pattern);
		});
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

void Grid::searchLocalArea(Node*& _startNode, int iterations_)
{
	UnMarkNodes();

	std::queue <Node*> nodeQueue;
	int currentIteration = 0;
	nodeQueue.push(_startNode);
	nodeQueue.front()->setMarked();

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty() && currentIteration< iterations_)
	{
		nodeQueue.front()->debugShape->setFillColor(sf::Color(223, 123, 123, 66));
		currentIteration++;
		auto neighbours = nodeQueue.front()->getNeighbours();
		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false)
			{
				neighbour->setMarked();
				nodeQueue.push(neighbour);
			}
		}
		nodeQueue.pop();
	}
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

		for(auto* node : tempGrid)
		{
			int landCount = 0;

			for(auto neighbour : node->getNeighbours())
			{
				if(neighbour->getIsLand())
				{
					landCount++;
				}
			}
	
			if(landCount > 4)
			{
				node->drawableNode->setTexture(TextureManager::getInstance().getTexture("landTile"));
				node->setParentTileType(LAND);
				node->setLand(true);
			}else
			{
				node->drawableNode->setTexture(TextureManager::getInstance().getTexture("waterTile"));
				node->setParentTileType(WATER);
				node->setTileType(DEFAULT_WATER);
				node->setLand(false);
			}
		}
		// Now apply changes back to the original nodeGrid
		for (size_t j = 0; j < nodeGrid.size(); j++)
		{
			nodeGrid[j]->setLand(tempGrid[j]->getIsLand());
			nodeGrid[j]->drawableNode->setTexture(*tempGrid[j]->drawableNode->getTexture());
			nodeGrid[j]->setTileType(tempGrid[j]->getTileType());

			//Uncomment for debug
		/*	drawGrid(m_window);
			m_window.display();
			wait(1);*/
		}
		// Clean up the temporary grid
		for (Node* node : tempGrid)
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
	/*	drawGrid(m_window);
		m_window.display();
		wait(1);*/
		//node->debugShape.setFillColor(sf::Color(123, 123, 123, 123));

		if(node->getMarked() == false && node->getIsLand())
		{
			MapIsland(node->getChunkId(),false ,m_window);
		}
	}
	UnMarkNodes();
	SaveIslandData(m_window);
}

///Kind of WFC but not really
void Grid::MapIsland(int _startIndex,bool saveIslandData, sf::RenderWindow & window)
{
	std::vector<Node*> currentIsland;
	std::queue <Node*> nodeQueue;

	nodeQueue.push(nodeGrid[_startIndex]);
	nodeQueue.front()->setMarked();

	currentIsland.push_back(nodeQueue.front());

	//nodeQueue.front()->debugShape.setFillColor(sf::Color(23,23,23,66));
	//nodeQueue.front()->drawDebug = true;

	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		FilterTiles(nodeQueue.front());

		//nodeQueue.front()->debugShape.setFillColor(sf::Color(123, 123, 123, 66));
		//drawGrid(window);
		//window.display();
		//wait(1);


		auto neighbours = nodeQueue.front()->getNeighbours();
		for (auto neighbour : neighbours)
		{
			if (neighbour->getMarked() == false)
			{
				neighbour->setMarked();
				if (neighbour->getIsLand()) 
				{
					currentIsland.push_back(neighbour);
					nodeQueue.push(neighbour);
					FilterTiles(neighbour);

				/*	if (saveIslandData) {
						neighbour->debugShape.setFillColor(sf::Color(23, 23, 23, 66));
					}*/
				/*	drawGrid(window);
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
			MapIsland(node->getChunkId(),true, window);
		}
	}
}

//removes edge tiles so chunk edge is always water
void Grid::removeWorldEdges(Node* _currentNode) const
{
	_currentNode->setParentTileType(WATER);
	_currentNode->setTileType(DEFAULT_WATER);
	_currentNode->setLand(false);
	determineTileTexture(_currentNode);
}

void Grid::UnMarkNodes()
{
	for (auto node : nodeGrid)
	{
		node->resetMarked();
		node->debugShape->setFillColor(sf::Color::Transparent);
	}
}

//removes edge cases of single nodes sticking out, expands on them
void Grid::replaceUndesiredLand(Node* _node) const
{
	_node->resetMarked();
	_node->setLand(false);
	_node->setParentTileType(WATER);
	_node->setTileType(DEFAULT_WATER);
	determineTileTexture(_node);
	for (auto neigh : _node->getNeighbours())
	{
		neigh->resetMarked();
		_node->setLand(false);
		_node->setParentTileType(WATER);
		_node->setTileType(DEFAULT_WATER);
		determineTileTexture(_node);
	}
}

//set texture 
void Grid::determineTileTexture(Node* _node) const
{
	switch (_node->getTileType())
	{
	case DEFAULT_WATER:
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("waterTile"));
		break;
	case GRASSY_LAND:
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("grassyLandTile"));
		break;
	case DEFAULT_SAND:
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("sandTile"));
		break;
	case DEFAULT_LAND:
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("landTile"));
		break;
	case TR_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("TRsandTile"));
		break;

	case TL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("TLsandTile"));
		break;

	case BR_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("BRsandTile"));
		break;

	case BL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("BLsandTile"));
		break;

	case FT_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("flatTop"));
		break;

	case FB_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("flatBottom"));
		break;

	case FR_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("flatRight"));
		break;

	case FL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("flatLeft"));
		break;

	case TR_LL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("LLSANDTR"));
		break;

	case TL_LL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("LLSANDTL"));
		break;

	case BR_LL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("LLSANDBR"));
		break;

	case BL_LL_SAND:
		_node->setWaterTexture(TextureManager::getInstance().getTexture("waterTile"));
		_node->drawableNode->setTexture(TextureManager::getInstance().getTexture("LLSANDBL"));
		break;

	default:
		break;
	}
}

void Grid::determineSandTileType(Node* _node) const
{
	switch (FollowsPatterns(_node, sandCornerPatterns))
	{
	case 0:
		_node->setParentTileType(SAND);
		_node->setTileType(TL_SAND);
		break;
	case 1:
		_node->setParentTileType(SAND);
		_node->setTileType(TR_SAND);
		break;
	case 2:
		_node->setParentTileType(SAND);
		_node->setTileType(BR_SAND);
		break;
	case 3:
		_node->setParentTileType(SAND);
		_node->setTileType(BL_SAND);
		break;
	case 4:
		_node->setParentTileType(SAND);
		_node->setTileType(FT_SAND);
		break;
	case 5:
		_node->setParentTileType(SAND);
		_node->setTileType(FB_SAND);
		break;
	case 6:
		_node->setParentTileType(SAND);
		_node->setTileType(FR_SAND);
		break;
	case 7:
		_node->setParentTileType(SAND);
		_node->setTileType(FL_SAND);
		break;
	case 8:
		_node->setParentTileType(SAND);
		_node->setTileType(TL_LL_SAND);
		break;
	case 9:
		_node->setParentTileType(SAND);
		_node->setTileType(BL_LL_SAND);
		break;
	case 10:
		_node->setParentTileType(SAND);
		_node->setTileType(TR_LL_SAND);
		break;
	case 11:
		_node->setParentTileType(SAND);
		_node->setTileType(BR_LL_SAND);
		break;
	}
}

void Grid::determineLandTileType(Node* _node) const
{
	int random = std::rand() % 100;
	switch (FollowsPatterns(_node, landPatterns))
	{
	case 0:
		_node->setParentTileType(LAND);
		if(random < 70)
		{
			_node->setTileType(GRASSY_LAND);
		}
		else {
			_node->setTileType(DEFAULT_LAND);
		}
		break;
	}
}

void Grid::determineWaterTileType(Node* _node) const
{
	if(!_node->getIsLand())
	{
		_node->setTileType(DEFAULT_WATER);
	}
}

void Grid::deleteSprites() const
{
	for(auto node : nodeGrid)
	{
		node->waterBackSprite.reset();
		node->drawableNode.reset();
	}
}





