#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for (auto& object : gameObjects)
	{
		object->render(window);
	}
}

void Island::update() const
{
	for(auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
}

void Island::positionGameObjects() const
{
	bool condition = false;
	for (auto& node : landNodes)
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
