#pragma once
#include"Includes.h"
#include"Node.h"
#include"Barrel.h"

class Island
{
public:
	Island() {}
	Island(std::vector<Node*>& _land) : landNodes(_land)
	{
		gameObjects.push_back(std::move(std::make_shared<Barrel>()));
		positionGameObjects();
	};

	void render(sf::RenderWindow& _win) const;
	void update();

	void positionGameObjects();

	std::vector<Node*> getLandNodes() const { return landNodes; }
	const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const {
		return gameObjects;
	}
private:
	std::vector<Node*> landNodes;

	std::vector<std::shared_ptr<GameObject>> gameObjects;
};

