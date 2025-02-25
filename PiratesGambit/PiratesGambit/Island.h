#pragma once
#include"Includes.h"
#include"Node.h"
#include"Barrel.h"
#include"BuccaneerBuilding.h"
#include "Enemy.h"
#include "GunnerBuilding.h"
#include "DiskSampling.h"
#include "Tree.h"

/// <summary>
/// Holds individual Islands inside a given chunk and holds game objects on those islands
/// </summary>
class Island
{
public:
	Island() {}
	Island(const std::vector<std::shared_ptr<Node>>& _land, const std::shared_ptr<Player>& _playerRef) : landNodes(_land)
	{
		playerRef = _playerRef;

		GenerateBuildings(3);
	}

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update(float _dt) const;

	void GenerateTrees(std::vector<std::shared_ptr<Node>>& _nodes);
	void GenerateBarrels(std::vector<std::shared_ptr<Node>>& _nodes);

	int CalculateTreeCount(int landNodes);
	std::vector<int> DistributeTreesIntoClumps(int totalTrees);

	int CalculateBarrelCount(int islandSize);

	void UnmarkNodes();
	void MarkNodes();

	void GenerateBuildings(int buildingCount);
	void Mark3x3Area(const std::shared_ptr<Node>& _startNode, const std::shared_ptr<Building>& _building) const;

	void PlaceEnemy(const std::shared_ptr<Enemy>& _enemy);


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

	//
	std::shared_ptr<Player> playerRef;
};

