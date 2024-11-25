#include "BattleScene.h"

void BattleScene::placeUnits()
{
	for(auto& unit: playerRef->getArmy()->getArmy())
	{
		for(auto& node : startArea)
		{
			if(!node->isOccupied())
			{
				unit->placeUnit(node->getMidPoint());
				node->updateOccupied(true);
				break; //end loop
			}
		}
	}
}

void BattleScene::update()
{
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->update();
	}
}

void BattleScene::render(sf::RenderWindow& _win) const
{
	_win.setView(_win.getDefaultView());
	for(auto& node: battleGrid)
	{
		_win.draw(*node->debugShape);
	}
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->render(_win);
	}
}

void BattleScene::initialiseBattleGrid()
{
	sf::Vector2f offset{ 300,200 };

	for (int y = 0; y < rowAmount; y++)
	{
		for (int x = 0; x < colAmount; x++)
		{
			battleGrid.push_back(std::make_shared<BattleGridNode>(offset.x + x * nodeSize, offset.y + y * nodeSize, nodeSize));
		}
	}
	//Setup id's first
	int max = rowAmount * colAmount;
	for (int i = 0; i < max; i++)
	{
		battleGrid[i]->setID(i);
		addNeighbours(i);
	}
}

void BattleScene::addNeighbours(int _currentNodeId) const
{
	int row = _currentNodeId / rowAmount;
	int col = _currentNodeId % colAmount;
	int neighbourIndex = -1;

	//This neighbour algoritihim prioritises vertical/hjorizontal then diagonal
	std::array<int, 4> directionOrder
	{
		1,3,5,7 //exclude 4 since that is our cell
	};
	for (auto& direction : directionOrder) {

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < rowAmount && n_col >= 0 && n_col < colAmount) {
			neighbourIndex = n_row * colAmount + n_col;
			battleGrid[_currentNodeId]->addNeighbour(battleGrid[neighbourIndex]);
		}
	}
}

void BattleScene::initialiseStartArea()
{
	for(int y = 0; y < rowAmount; y++)
	{
		for(int x = 0; x < 2; x++)
		{
			int nodeID = y * colAmount + x;
			startArea.push_back(battleGrid[nodeID]);
		}
	}
}
