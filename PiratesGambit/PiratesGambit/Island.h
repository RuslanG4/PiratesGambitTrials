#pragma once
#include"Includes.h"
#include"Node.h"
#include"Barrel.h"
#include"BuccaneerBuilding.h"
#include"CannonBuilding.h"
#include"BirdBuilding.h"
#include"HarpoonerBuilding.h"
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
	Island(const std::vector<std::shared_ptr<Node>>& _land, const std::shared_ptr<Player>& _playerRef) : landNodes(_land)
	{
		playerRef = _playerRef;

		for(auto& node : landNodes)
		{
			if(node->getParentTileType() == SAND)
			{
				sandNodes.push_back(node);
			}
		}

		GenerateIsland();
	}
	/// <summary>
	/// Draws island
	/// </summary>
	/// <param name="window">RenderWindow</param>
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;


	void RenderUI(const std::unique_ptr<sf::RenderWindow>& window) const;

	/// <summary>
	/// Updates all objects in island
	/// </summary>
	/// <param name="_dt">Delta time</param>
	void update(float _dt) const;

	/// <summary>
	/// Generates objects on the island
	/// </summary>
	void GenerateIsland();

	/// <summary>
	/// Generates trees
	/// </summary>
	/// <param name="_nodes">Search Space</param>
	void GenerateTrees(std::vector<std::shared_ptr<Node>>& _nodes);

	/// <summary>
	/// Generates Buildings
	/// </summary>
	/// <param name="buildingCount">amount of buildings</param>
	/// <param name="_nodes">SearchSpace</param>
	void GenerateBuildings(int buildingCount, std::vector<std::shared_ptr<Node>>& _nodes);

	/// <summary>
	/// Generates Barrels
	/// </summary>
	/// <param name="_nodes">Search Space</param>
	void GenerateBarrels(std::vector<std::shared_ptr<Node>>& _nodes);

	/// <summary>
	/// Calculates the amount of trees an island should have
	/// </summary>
	/// <param name="landNodes">Amount of land</param>
	/// <returns>how many trees</returns>
	int CalculateTreeCount(int landNodes);

	/// <summary>
	/// Splits the trees into clumped groups
	/// </summary>
	/// <param name="totalTrees">Total trees on island</param>
	/// <returns>vector of clumps</returns>
	std::vector<int> DistributeTreesIntoClumps(int totalTrees);

	/// <summary>
	/// Sees how many barrels an island should have
	/// </summary>
	/// <param name="islandSize">Size of island</param>
	/// <returns>how many barrels</returns>
	int CalculateBarrelCount(int islandSize);

	/// <summary>
	/// Marks nodes for continuation of chunk generations as there may be more islands
	/// </summary>
	void MarkNodes();

	/// <summary>
	/// Marks area around the trees to give more chances of buildings spawning
	/// </summary>
	void MarkAreaAroundTrees();

	/// <summary>
	/// Clears area of Building occupied boolean
	/// </summary>
	void ClearIslandNodeConditions();

	/// <summary>
	/// Marks a 3x3 area for a building so that the nodes can be interacted with
	/// </summary>
	/// <param name="_startNode">Start node</param>
	/// <param name="_building">Building to hold node IDs</param>
	void Mark3x3Area(const std::shared_ptr<Node>& _startNode, const std::shared_ptr<Building>& _building) const;

	void PlaceEnemy(const std::shared_ptr<Enemy>& _enemy);


	const std::vector<std::shared_ptr<Node>>& getLandNodes() const { return landNodes; }
	const std::vector<std::shared_ptr<Node>>& getSandNodes() const { return sandNodes; }
	const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const { return gameObjects; }
	const std::vector<std::shared_ptr<Building>>& getBuildings() const { return buildings; }
private:
	//land node storage
	std::vector<std::shared_ptr<Node>> landNodes;
	//sand nodes storage
	std::vector<std::shared_ptr<Node>> sandNodes;
	//game object storage
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	//buildings
	std::vector<std::shared_ptr<Building>> buildings;

	//player ref
	std::shared_ptr<Player> playerRef;
};

