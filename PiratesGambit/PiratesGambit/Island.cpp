#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for (auto& object : buildings)
	{
		object->Render(window);
	}
}

void Island::update(float _dt) const
{
	for(auto& gameObject : buildings)
	{
		gameObject->Update(_dt);
	}
}

bool Island::CanPlaceObject()
{
	return false;
}

void Island::positionGameObjects()
{
	bool condition = false;
	for (auto& node : landNodes)
	{
		if (node->getParentTileType() == LAND && allNeighboursAreLand(node))
		{ 
			for (auto& object : buildings)
			{
				object->SetPosition(node->getMidPoint());
				//
				object->AddToOccupiedNodes(node->getID());
				node->isOccupied = true;
				for(auto& neighbourID : node->getNeighbours())
				{
					object->AddToOccupiedNodes(neighbourID->getID());
					neighbourID->isOccupied = true;
				}
				//object->setNodeId(node->getID());
				condition = true;
				break;
			}
		}
		if(condition)
		{
			break;
		}
	}
}

void Island::PlaceEnemy(const std::shared_ptr<Enemy>& _enemy)
{
	for (auto& node : landNodes)
	{
		if (node->getParentTileType() == LAND && !node->isOccupied)
		{
			_enemy->updatePosition(node->getMidPoint());
			_enemy->setCurrentNode(node->getID());
			break;
		}
	}
}

bool Island::allNeighboursAreLand(const std::shared_ptr<Node>& node)
{
	int parentTileType = node->getParentTileType();

	return std::ranges::all_of(node->getNeighbours(), [parentTileType](const auto& neighbour) {
		return neighbour->getParentTileType() == parentTileType;
		});
}
