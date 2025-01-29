#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for (auto& object : buildings)
	{
		object->Render(window);
	}
}

void Island::update() const
{
	for(auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
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
				for(auto& neighbourID : node->getNeighbours())
				{
					object->AddToOccupiedNodes(neighbourID->getID());
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

bool Island::allNeighboursAreLand(const std::shared_ptr<Node>& node)
{
	int parentTileType = node->getParentTileType();

	return std::ranges::all_of(node->getNeighbours(), [parentTileType](const auto& neighbour) {
		return neighbour->getParentTileType() == parentTileType;
		});
}
