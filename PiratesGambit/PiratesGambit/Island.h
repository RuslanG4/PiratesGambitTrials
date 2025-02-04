#pragma once
#include"Includes.h"
#include"Node.h"
#include"Barrel.h"
#include"BuccaneerBuilding.h"
#include "Enemy.h"
#include "GunnerBuilding.h"

/// <summary>
/// Holds individual Islands inside a given chunk and holds game objects on those islands
/// </summary>
class Island
{
public:
	Island() {}
	Island(const std::vector<std::shared_ptr<Node>>& _land, const std::shared_ptr<Player>& _playerRef) : landNodes(_land)
	{
		gameObjects.push_back(std::make_shared<Barrel>());
		buildings.push_back(std::make_shared<GunnerBuilding>(_playerRef));
		positionGameObjects();
	};

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update(float _dt) const;

	bool CanPlaceObject();
	void positionGameObjects();

	void PlaceEnemy(const std::shared_ptr<Enemy>& _enemy);

	bool allNeighboursAreLand(const std::shared_ptr<Node>&);

	const std::vector<std::shared_ptr<Node>>& getLandNodes() const { return landNodes; }
	const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const { return gameObjects; }
	const std::vector<std::shared_ptr<Building>>& getBuildings() const { return buildings; }
private:
	//land node storage
	std::vector<std::shared_ptr<Node>> landNodes;
	//game object storage
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	//buildings
	std::vector<std::shared_ptr<Building>> buildings;

};

