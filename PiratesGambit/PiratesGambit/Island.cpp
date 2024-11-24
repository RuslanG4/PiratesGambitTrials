#include "Island.h"

void Island::render(sf::RenderWindow& _win) const
{
	for (auto& object : gameObjects)
	{
		object->render(_win);
	}
}

void Island::update()
{
	for(auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
}

void Island::positionGameObjects()
{
	bool condition = false;
	for (auto* node : landNodes)
	{
		if (node->getParentTileType() == LAND)
		{
			for (auto& object : gameObjects)
			{
				object->setPosition(node->getMidPoint());
				object->setNodeId(node->getID());
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
