#pragma once
#include"Includes.h"
#include"Node.h"
#include"Barrel.h"

/// <summary>
/// Holds individual Islands inside a given chunk and holds game objects on those islands
/// </summary>
class Island
{
public:
	Island() {}
	Island(const std::vector<std::shared_ptr<Node>>& _land) : landNodes(_land)
	{
		gameObjects.push_back(std::move(std::make_shared<Barrel>()));
		positionGameObjects();
	};

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update() const;

	void positionGameObjects() const;

	const std::vector<std::shared_ptr<Node>>& getLandNodes() const { return landNodes; }
	const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const { return gameObjects; }
private:
	//land node storage
	std::vector<std::shared_ptr<Node>> landNodes;
	//game object storage
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};

