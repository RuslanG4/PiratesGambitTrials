#include "Grid.h"

Grid::Grid(const std::vector<std::shared_ptr<Node>>& gridNodes_, const std::shared_ptr<Player>& _playerRef) : nodeGrid(gridNodes_)
{
	playerRef = _playerRef;
	chunkStartX = nodeGrid[0]->getPosition().x;
	chunkEndX = nodeGrid[nodeGrid.size() - 1]->getPosition().x + (nodeGrid[0]->getNodeData().size);

	chunkStartY = nodeGrid[0]->getPosition().y;
	chunkEndY = nodeGrid[nodeGrid.size() - 1]->getPosition().y + (nodeGrid[0]->getNodeData().size);
}

/// <summary>
/// renders nodes for visual debugging in generation
/// </summary>
/// <param name="_window">sfml render window</param>
void Grid::drawGrid(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for(auto& node : nodeGrid)
	{
		if(node->waterBackSprite && node->drawableNode)
		{
			window->draw(*(node->waterBackSprite));
			window->draw(*(node->drawableNode));
		}
		window->draw(*(node->debugShape));
	}
}

/// <summary>
/// passes render window to island in order to draw objects
/// </summary>
/// <param name="_window">sfml render window</param>
void Grid::drawGameObject(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for(auto& island : islands)
	{
		island->render(window);
	}
}

/// <summary>
/// updates islands
/// </summary>
void Grid::updateIslands(float _dt) const
{
	for (auto& island : islands)
	{
		island->update(_dt);
	}
}

/// <summary>
/// Determines the state of an individual tile
/// </summary>
/// <param name="_currentNode"></param>
void Grid::FilterTiles(std::shared_ptr<Node>& _currentNode) const
{
	if (filterUndesiredTiles(_currentNode))
	{
		replaceUndesiredLand(_currentNode);
	}
	if (_currentNode->getNodeData().neighbourIDs.size() < 8)
	{
		removeWorldEdges(_currentNode);
	}
	determineLandTileType(_currentNode);
	determineSandTileType(_currentNode);
	determineWaterTileType(_currentNode);
	determineTileTexture(_currentNode);
}

///<summary>
///Checks sand tile texture rules
///</summary>
int Grid::FollowsPatterns(const std::shared_ptr<Node>& _currentNode, const std::vector<std::vector<std::pair<int, bool>>>& _pattern) const
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

///<summary>
/// Checks water tile texture rules
///</summary>
bool Grid::FilterWaterTiles(const std::shared_ptr<Node>& _currentNode) const
{
	return std::ranges::any_of(undesiredLandTiles, [&](const auto& pattern) {
		return CheckPattern(_currentNode, pattern);
		});
}

///<summary>
/// Checks undesired tile rules
///</summary>
bool Grid::filterUndesiredTiles(const std::shared_ptr<Node>& _currentNode) const
{
	return std::ranges::any_of(undesiredTiles, [&](const auto& pattern) {
		return CheckPattern(_currentNode, pattern);
		});
}

///<summary>
/// takes in patterns and cross checks neighbours to see if match
///</summary>
bool Grid::CheckPattern(const std::shared_ptr<Node>& _currentNode, const std::vector<std::pair<int, bool>>& _pattern) const
{
	int patternCount = 0;
	for (int i = 0; i < _pattern.size(); i++)
	{
		if (_currentNode->getNodeData().neighbourIDs.size() > 5) {
			if (_currentNode->getNeighbours()[_pattern[i].first].first->getIsLand() == _pattern[i].second)
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

/// <summary>
/// Slow down for visual debugging for generation
/// </summary>
/// <param name="time">how slow</param>
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

/// <summary>
/// Celuar Automata algorithm for shape generation
/// </summary>
/// <param name="_interations">How many times we do algorithm</param>
void Grid::ApplyCellular(int _interations, const std::unique_ptr<sf::RenderWindow>& window)
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

			for(auto& neighbour : node->getNeighbours())
			{
				if(neighbour.first->getIsLand())
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
		//apply changes back to the original nodeGrid
		for (size_t j = 0; j < nodeGrid.size(); j++)
		{
			nodeGrid[j]->setLand(tempGrid[j]->getIsLand());
			nodeGrid[j]->drawableNode->setTexture(*tempGrid[j]->drawableNode->getTexture());
			nodeGrid[j]->setTileType(tempGrid[j]->getTileType());
		}
		// delete temp deep copied nodes 
		for (Node* node : tempGrid)
		{
			delete node;  
		}
	}

	FindLand(window);
}

///<summary>
/// Iterated through chunk to find any land nodes to start island mapping
///</summary>
void Grid::FindLand(const std::unique_ptr<sf::RenderWindow>& window)
{
	for(auto& node : nodeGrid)
	{
	/*	drawGrid(m_window);
		m_window.display();
		wait(1);*/
		//node->debugShape.setFillColor(sf::Color(123, 123, 123, 123));

		if(!node->hasBeenTraversed() && node->getIsLand())
		{
			MapIsland(node->getChunkId(),false ,window); //start island mapping
		}
	}
	UnMarkNodes();
	SaveIslandData(window);
	UnMarkNodes();
}

/// <summary>
/// Wave function collapse variation to generate tile textures
/// </summary>
/// <param name="_startIndex">Begin node</param>
/// <param name="saveIslandData">If we want to store in islands vector</param>
/// <param name="window">sfml window</param>
void Grid::MapIsland(int _startIndex,bool saveIslandData, const std::unique_ptr<sf::RenderWindow>& window)
{
	std::vector<std::shared_ptr<Node>> currentIsland;
	std::queue<std::shared_ptr<Node>> nodeQueue;

	nodeQueue.push(nodeGrid[_startIndex]);
	nodeQueue.front()->updateTraversed(true);

	currentIsland.push_back(nodeQueue.front());

	//nodeQueue.front()->debugShape.setFillColor(sf::Color(23,23,23,66));
	//nodeQueue.front()->drawDebug = true;
	// loop through the queue while there are nodes in it.
	while (!nodeQueue.empty())
	{
		FilterTiles(nodeQueue.front()); //determine tile 

		//std::cout << nodeQueue.front()->getChunkId()<<"\n";
		//nodeQueue.front()->debugShape->setFillColor(sf::Color(123, 123, 123, 66));
		//drawGrid(window);
		//window->display();
		//wait(1);

		auto neighbours = nodeQueue.front()->getNeighbours();
		for (auto& neighbour : neighbours)
		{
			if (!neighbour.first->hasBeenTraversed())
			{
				neighbour.first->updateTraversed(true);
				if (neighbour.first->getIsLand())
				{
					currentIsland.push_back(neighbour.first);
					nodeQueue.push(neighbour.first);
					FilterTiles(neighbour.first);

		/*			if (saveIslandData) {
						neighbour->debugShape->setFillColor(sf::Color(23, 23, 23, 66));
					}
					drawGrid(window);
					window.display();
					wait(1);*/
				}
			}
		}
		nodeQueue.pop();
		
	}
	if(saveIslandData)
	{
		islands.push_back((std::make_shared<Island>(currentIsland, playerRef)));
	}
	
}

///<summary>
/// Saves nodes to island 
///</summary>
void Grid::SaveIslandData(const std::unique_ptr<sf::RenderWindow>& window)
{
	for (auto& node : nodeGrid)
	{
		if (!node->hasBeenTraversed() && node->getIsLand())
		{
			MapIsland(node->getChunkId(),true, window);
		}
	}
}

/// <summary>
/// removes edge tiles so chunk edge is always water
/// </summary>
/// <param name="_currentNode"></param>
void Grid::removeWorldEdges(std::shared_ptr<Node>& _currentNode) const
{
	_currentNode->setParentTileType(WATER);
	_currentNode->setTileType(DEFAULT_WATER);
	_currentNode->setLand(false);
	determineTileTexture(_currentNode);
}

///<summary>
/// unmarks nodes for other graph algorithms
///</summary>
void Grid::UnMarkNodes() const
{
	for (auto& node : nodeGrid)
	{
		node->updateTraversed(false);
		//node->debugShape->setFillColor(sf::Color::Transparent);
	}
}

/// <summary>
/// removes edge cases of single nodes sticking out, expands on them
/// </summary>
/// <param name="_node">start node</param>
void Grid::replaceUndesiredLand(std::shared_ptr<Node>& _node) const
{
	_node->resetMarked();
	_node->setLand(false);
	_node->setParentTileType(WATER);
	_node->setTileType(DEFAULT_WATER);
	determineTileTexture(_node);
	for (auto& neighbour : _node->getNeighbours())
	{
		neighbour.first->updateTraversed(false);
		_node->setLand(false);
		_node->setParentTileType(WATER);
		_node->setTileType(DEFAULT_WATER);
		determineTileTexture(_node);
	}
}

/// <summary>
/// sets texture for tile based on switch
/// </summary>
/// <param name="_node">current node</param>
void Grid::determineTileTexture(const std::shared_ptr<Node>& _node) const
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

/// <summary>
///  determines what type of sand node is if follows patterns
/// </summary>
/// <param name="_node">current node</param>
void Grid::determineSandTileType(const std::shared_ptr<Node>& _node) const
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

void Grid::determineLandTileType(const std::shared_ptr<Node>& _node) const
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

void Grid::determineWaterTileType(const std::shared_ptr<Node>& _node) const
{
	if(!_node->getIsLand())
	{
		_node->setTileType(DEFAULT_WATER);
	}
}






