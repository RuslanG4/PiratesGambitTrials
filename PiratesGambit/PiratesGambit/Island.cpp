#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for (auto& object : buildings)
	{
		object->Render(window);
	}
	for (auto& gameObject : gameObjects)
	{
		gameObject->render(window);
	}
}

void Island::update(float _dt) const
{
	for(auto& gameObject : buildings)
	{
		gameObject->Update(_dt);
	}
	for (auto& gameObject : gameObjects)
	{
		gameObject->update();
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
				node->updateOccupied(true);
				for(auto& neighbourID : node->getNeighbours())
				{
					object->AddToOccupiedNodes(neighbourID.first->getID());
					neighbourID.first->updateOccupied(true);
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

	PlaceBarrels();
}

void Island::PlaceBarrels()
{
	bool condition = false;
	for (auto& node : landNodes)
	{
		if (node->getParentTileType() == LAND && !node->isOccupied())
		{
			for(auto& object : gameObjects)
			{
				object->setPosition(node->getMidPoint());
				object->setNodeId(node->getID());
				node->updateOccupied(true);
				condition = true;
				break;
			}
		}
		if (condition)
		{
			break;
		}
	}
}

void Island::PlaceEnemy(const std::shared_ptr<Enemy>& _enemy)
{
	for (auto& node : landNodes)
	{
		if (node->getParentTileType() == LAND && !node->isOccupied())
		{
			_enemy->updatePosition(node->getMidPoint());
			break;
		}
	}
}

bool Island::allNeighboursAreLand(const std::shared_ptr<Node>& node)
{
	int parentTileType = node->getParentTileType();

	return std::ranges::all_of(node->getNeighbours(), [parentTileType](const auto& neighbour) {
		return neighbour.first->getParentTileType() == parentTileType;
		});
}
